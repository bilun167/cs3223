/*-------------------------------------------------------------------------
 *
 * freelist.c
 *	  routines for managing the buffer pool's replacement strategy.
 *
 *
 * Portions Copyright (c) 1996-2013, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/backend/storage/buffer/freelist.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "storage/buf_internals.h"
#include "storage/bufmgr.h"

#define NOT_IN_STACK -1
struct StackNode{
	int buf_id;
	int next;
	int prev;
};

typedef struct StackNode StackNode;
/*
 * The shared freelist control information.
 */
typedef struct
{
	/* Clock sweep hand: index of next buffer to consider grabbing */
	int			nextVictimBuffer;

	int			firstFreeBuffer;	/* Head of list of unused buffers */
	int			lastFreeBuffer; /* Tail of list of unused buffers */

	/*
	 * NOTE: lastFreeBuffer is undefined when firstFreeBuffer is -1 (that is,
	 * when the list is empty)
	 */

	/*
	 * Statistics.	These counters should be wide enough that they can't
	 * overflow during a single bgwriter cycle.
	 */
	uint32		completePasses; /* Complete cycles of the clock sweep */
	uint32		numBufferAllocs;	/* Buffers allocated since last reset */

	/*
	 * Notification latch, or NULL if none.  See StrategyNotifyBgWriter.
	 */
	Latch	   *bgwriterLatch;

	
	int tail;
	int head;
	int size;
	int freePos;
} BufferStrategyControl;

/* Pointers to shared state */
static BufferStrategyControl *StrategyControl = NULL;
// Variable size 
static StackNode *LRUStack = NULL;
//static int *PageAccessedTime = NULL;

/*
 * Private (non-shared) state for managing a ring of shared buffers to re-use.
 * This is currently the only kind of BufferAccessStrategy object, but someday
 * we might have more kinds.
 */
typedef struct BufferAccessStrategyData
{
	/* Overall strategy type */
	BufferAccessStrategyType btype;
	/* Number of elements in buffers[] array */
	int			ring_size;

	/*
	 * Index of the "current" slot in the ring, ie, the one most recently
	 * returned by GetBufferFromRing.
	 */
	int			current;

	/*
	 * True if the buffer just returned by StrategyGetBuffer had been in the
	 * ring already.
	 */
	bool		current_was_in_ring;

	/*
	 * Array of buffer numbers.  InvalidBuffer (that is, zero) indicates we
	 * have not yet selected a buffer for this ring slot.  For allocation
	 * simplicity this is palloc'd together with the fixed fields of the
	 * struct.
	 */
	Buffer		buffers[1];		/* VARIABLE SIZE ARRAY */
}	BufferAccessStrategyData;

/* Prototypes for internal functions */
static volatile BufferDesc *GetBufferFromRing(BufferAccessStrategy strategy);
static void AddBufferToRing(BufferAccessStrategy strategy,
				volatile BufferDesc *buf);

void printStack(){
	// Print the stack trace from head to tail
	StackNode *curNode = &LRUStack[StrategyControl->head];
	int j = 0;
	for (j = 0; j<StrategyControl->size ; j++){
		printf("%d -> ",curNode->buf_id);
		curNode = &LRUStack[curNode->next];
	}
	printf("\n\n");
}
// cs3223
// Updates the LRU stack for an accessed buffer page 
// buf_id = identifier of accessed buffer page
void 
StrategyUpdateAccessedBuffer(int buf_id)
{
	StackNode *curNode = 0;
	//printf("Inserting : %d [ ",buf_id);
	// if LRU_Stack is empty -> insert the head
	//elog(LOG,"Inside StUpAccBu, size = %d ", StrategyControl->size);
	//printf("Inside StUpAccBu, size = %d head =%d tail= %d , buf_id = %d \n", StrategyControl->size,StrategyControl->head,StrategyControl->tail,buf_id);
	if (!StrategyControl->size){
		// Create new node
		LRUStack[0].buf_id = buf_id;
		LRUStack[0].prev = NOT_IN_STACK;
		LRUStack[0].accessed_time = 0;
		StrategyControl->tail = 0;
		StrategyControl->head = 0;
		StrategyControl->size++;
		if (StrategyControl->size <=NBuffers)
			StrategyControl->freePos = StrategyControl->size;
		else
			StrategyControl->freePos = NOT_IN_STACK;
	} else{
		// Find the Node in the Stack
		curNode = &LRUStack[StrategyControl->head];
		int i = 0;
		for (i=0;i <StrategyControl->size ;i++){
			curNode = &LRUStack[i];
			if (curNode->buf_id == buf_id)
				break;
		}
		if (i < StrategyControl->size){ // found the node with the buf_id
			volatile BufferDesc *buf;
			
			//Main bug lies HERE: unpin page -> reset accessed_time to zero
			buf = &BufferDescriptors[curNode->buf_id];
			if (buf->usage_count) 
				curNode->accessed_time++;
			else curNode->accessed_time = 0;
			if (i != StrategyControl->head) { // if the position is the head -> do nothing
				if (i==StrategyControl->tail){ // tail position-> new tail
					LRUStack[curNode->prev].next = NOT_IN_STACK; // position of the new tail next 	
					StrategyControl->tail = curNode->prev; // new tail position
					curNode->next = StrategyControl->head; // next position of the new head is the old head
					curNode->prev = NOT_IN_STACK;				
				}else{ // middle of the two node
					//printf("middle curNode id = %d , curNode  next = %d ,curNode prev = %d\n",curNode->buf_id,curNode->next, curNode->prev);
					LRUStack[curNode->prev].next = curNode->next;		// next of prev is next of cur
					LRUStack[curNode->next].prev = curNode->prev;		// prev of next is prev of cur
					curNode->next = StrategyControl->head; // next position of the new head is the old head
					curNode->prev = NOT_IN_STACK;
				}
				LRUStack[StrategyControl->head].prev = i;
					StrategyControl->head = i;		// update the head position
			}
		}else{ // Not found, insert to the next free slot:
			//printf("new node, free slot = %d \n", StrategyControl->freePos);
			curNode = &LRUStack[StrategyControl->freePos];
			curNode->prev = NOT_IN_STACK;
			curNode->next = StrategyControl->head; // next position of the new head is the old head
			curNode->accessed_time = 0;
			LRUStack[StrategyControl->head].prev = i;
			curNode->buf_id = buf_id;
			StrategyControl->head = i;		// update the head position
			StrategyControl->size++;
			if (StrategyControl->size <=NBuffers)
				StrategyControl->freePos = StrategyControl->size;
			else
				StrategyControl->freePos = NOT_IN_STACK;
		}
	}
	//printStack();
}


/*
 * StrategyGetBuffer
 *
 *	Called by the bufmgr to get the next candidate buffer to use in
 *	BufferAlloc(). The only hard requirement BufferAlloc() has is that
 *	the selected buffer must not currently be pinned by anyone.
 *
 *	strategy is a BufferAccessStrategy object, or NULL for default strategy.
 *
 *	To ensure that no one else can pin the buffer before we do, we must
 *	return the buffer with the buffer header spinlock still held.  If
 *	*lock_held is set on exit, we have returned with the BufFreelistLock
 *	still held, as well; the caller must release that lock once the spinlock
 *	is dropped.  We do it that way because releasing the BufFreelistLock
 *	might awaken other processes, and it would be bad to do the associated
 *	kernel calls while holding the buffer header spinlock.
 */
volatile BufferDesc *
StrategyGetBuffer(BufferAccessStrategy strategy, bool *lock_held)
{
	volatile BufferDesc *buf;
	Latch	   *bgwriterLatch;
	//elog(DEBUG2, "Get buffer ");
	//elog(LOG, "Strategy first free buffer is %d ", StrategyControl->firstFreeBuffer);
		//elog(LOG, "Get buffer:Stack size is %d ", StrategyControl->size);
	/*
	 * If given a strategy object, see whether it can select a buffer. We
	 * assume strategy objects don't need the BufFreelistLock.
	 */
	if (strategy != NULL)
	{
		buf = GetBufferFromRing(strategy);
		if (buf != NULL)
		{
			*lock_held = false;
			StrategyUpdateAccessedBuffer(buf->buf_id);
			return buf;
		}
	}

	/* Nope, so lock the freelist */
	*lock_held = true;
	LWLockAcquire(BufFreelistLock, LW_EXCLUSIVE);

	/*
	 * We count buffer allocation requests so that the bgwriter can estimate
	 * the rate of buffer consumption.	Note that buffers recycled by a
	 * strategy object are intentionally not counted here.
	 */
	StrategyControl->numBufferAllocs++;

	/*
	 * If bgwriterLatch is set, we need to waken the bgwriter, but we should
	 * not do so while holding BufFreelistLock; so release and re-grab.  This
	 * is annoyingly tedious, but it happens at most once per bgwriter cycle,
	 * so the performance hit is minimal.
	 */
	bgwriterLatch = StrategyControl->bgwriterLatch;
	if (bgwriterLatch)
	{
		StrategyControl->bgwriterLatch = NULL;
		LWLockRelease(BufFreelistLock);
		SetLatch(bgwriterLatch);
		LWLockAcquire(BufFreelistLock, LW_EXCLUSIVE);
	}

	/*
	 * Try to get a buffer from the freelist.  Note that the freeNext fields
	 * are considered to be protected by the BufFreelistLock not the
	 * individual buffer spinlocks, so it's OK to manipulate them without
	 * holding the spinlock.
	 */
	while (StrategyControl->firstFreeBuffer >= 0)
	{
		buf = &BufferDescriptors[StrategyControl->firstFreeBuffer];
		Assert(buf->freeNext != FREENEXT_NOT_IN_LIST);

		/* Unconditionally remove buffer from freelist */
		StrategyControl->firstFreeBuffer = buf->freeNext;
		buf->freeNext = FREENEXT_NOT_IN_LIST;

		/*
		 * If the buffer is pinned or has a nonzero usage_count, we cannot use
		 * it; discard it and retry.  (This can only happen if VACUUM put a
		 * valid buffer in the freelist and then someone else used it before
		 * we got to it.  It's probably impossible altogether as of 8.3, but
		 * we'd better check anyway.)
		 */
		LockBufHdr(buf);
		if (buf->refcount == 0 && buf->usage_count == 0)
		{
			if (strategy != NULL)
				AddBufferToRing(strategy, buf);
			StrategyUpdateAccessedBuffer(buf->buf_id);
			return buf;
		}
		UnlockBufHdr(buf);
	}

	/* Nothing on the freelist, so run the LRU algorithm */
	// initialized cur node to the least recently used( the tail of the stack) 
	StackNode* curNode = &LRUStack[StrategyControl->tail];
	StackNode* lastValidNode = curNode;
	//printf("Tail:%d \n",StrategyControl->tail);
	///elog(LOG, "Stack size is %d ", LRU_Control->size);
	if (StrategyControl->size>0){
		for (;;)
		{
			//elog(DEBUG4, "Find victim ");

			buf = &BufferDescriptors[curNode->buf_id];
			/*
			* If the buffer is pinned , we cannot use
			* move to the next least recently used buffer
			*/
			LockBufHdr(buf);
			if (buf->refcount == 0 && curNode->accessed_time <= 1)	// If pin count = 0 -> choose the victim buffer
			{
				if (strategy != NULL)
					AddBufferToRing(strategy, buf);
				StrategyUpdateAccessedBuffer(buf->buf_id);
				return buf;
			}
			UnlockBufHdr(buf);
			if (curNode->prev == NOT_IN_STACK)
			{
				//elog(ERROR, "No buffer");
				break;
				/*
				* We've scanned all the buffers without making any state changes,
				* so all the buffers are pinned (or were when we looked at them).
				* We could hope that someone will free one eventually, but it's
				* probably better to fail than to risk getting stuck in an
				* infinite loop.
				*/
				//elog(ERROR, "cur node is NULL");
			}
			curNode=&LRUStack[curNode->prev];
		}
		
		printf("S2\t");
		curNode = lastValidNode;
		int secondLeast_trigger;
		for (;;)
		{
			//elog(DEBUG4, "Find victim ");

			buf = &BufferDescriptors[curNode->buf_id];
			/*
			* If the buffer is pinned , we cannot use
			* move to the next least recently used buffer
			*/
			LockBufHdr(buf);
			if (buf->refcount == 0)	// If pin count = 0 -> choose the victim buffer
			{
				if (secondLeast_trigger) {
					if (strategy != NULL)
						AddBufferToRing(strategy, buf);
					StrategyUpdateAccessedBuffer(buf->buf_id);
					return buf;
				}
				else secondLeast_trigger = 1;
			}
			UnlockBufHdr(buf);
			if (curNode->prev == NOT_IN_STACK)
			{
				if (secondLeast_trigger) {
					buf = &BufferDescriptors[lastValidNode->buf_id];
					/*
					* If the buffer is pinned , we cannot use
					* move to the next least recently used buffer
					*/
					LockBufHdr(buf);
					if (buf->refcount == 0)	// If pin count = 0 -> choose the victim buffer
					{
						if (secondLeast_trigger) {
							if (strategy != NULL)
								AddBufferToRing(strategy, buf);
							StrategyUpdateAccessedBuffer(buf->buf_id);
							return buf;
						}
						else secondLeast_trigger = 1;
					}
					UnlockBufHdr(buf);
				}
				elog(ERROR, "No buffer");
				/*
				* We've scanned all the buffers without making any state changes,
				* so all the buffers are pinned (or were when we looked at them).
				* We could hope that someone will free one eventually, but it's
				* probably better to fail than to risk getting stuck in an
				* infinite loop.
				*/
				//elog(ERROR, "cur node is NULL");
			}
			curNode=&LRUStack[curNode->prev];
		}
	}else{
		elog(ERROR, "Stack size is %d ", StrategyControl->size);
	}
}

/* CS3223, delete the Node from LRU Stack*/
void DeleteLRU_Stack(int buf_id){
	// First we find the position of the node with the corresponding buf_id
	//elog(LOG, "Delete and Stack size is %d ", StrategyControl->size);
	StackNode* curNode = 0;
	int i = 0;
	for (i=0;i <StrategyControl->size ;i++){
		curNode = &LRUStack[i];
		if (curNode->buf_id == buf_id)
			break;
	}
	if (StrategyControl->size==1){
		StrategyControl->head = NOT_IN_STACK;
		StrategyControl->tail = NOT_IN_STACK;
		StrategyControl->freePos = 0;
	} else {
		StrategyControl->freePos = i;	// Position for free slot
		if (curNode->buf_id == StrategyControl->head){
			StrategyControl->head = curNode->next; // next head
			LRUStack[StrategyControl->head].prev = NOT_IN_STACK;
		} else if (curNode->buf_id == StrategyControl->tail){
			StrategyControl->tail = curNode->prev;	// position of the new tail
			LRUStack[StrategyControl->tail].next = NOT_IN_STACK;
		} else {
			LRUStack[curNode->prev].next = curNode->next;
			LRUStack[curNode->next].prev = curNode->prev;	
		}
	}
	curNode->next = NOT_IN_STACK;
	curNode->prev = NOT_IN_STACK;
	curNode->buf_id=NOT_IN_STACK;
	StrategyControl->size--;
}

/*
 * StrategyFreeBuffer: put a buffer on the freelist
 */
void
StrategyFreeBuffer(volatile BufferDesc *buf)
{
	LWLockAcquire(BufFreelistLock, LW_EXCLUSIVE);
	elog(DEBUG3, "Gonna free buffer ");
	/*
	 * It is possible that we are told to put something in the freelist that
	 * is already in it; don't screw up the list if so.
	 */
	if (buf->freeNext == FREENEXT_NOT_IN_LIST)
	{
		buf->freeNext = StrategyControl->firstFreeBuffer;
		if (buf->freeNext < 0)
			StrategyControl->lastFreeBuffer = buf->buf_id;
		StrategyControl->firstFreeBuffer = buf->buf_id;
		DeleteLRU_Stack(buf->buf_id);
	}

	LWLockRelease(BufFreelistLock);
}

/*
 * StrategySyncStart -- tell BufferSync where to start syncing
 *
 * The result is the buffer index of the best buffer to sync first.
 * BufferSync() will proceed circularly around the buffer array from there.
 *
 * In addition, we return the completed-pass count (which is effectively
 * the higher-order bits of nextVictimBuffer) and the count of recent buffer
 * allocs if non-NULL pointers are passed.	The alloc count is reset after
 * being read.
 */
int
StrategySyncStart(uint32 *complete_passes, uint32 *num_buf_alloc)
{
	int			result;

	LWLockAcquire(BufFreelistLock, LW_EXCLUSIVE);
	result = StrategyControl->nextVictimBuffer;
	if (complete_passes)
		*complete_passes = StrategyControl->completePasses;
	if (num_buf_alloc)
	{
		*num_buf_alloc = StrategyControl->numBufferAllocs;
		StrategyControl->numBufferAllocs = 0;
	}
	LWLockRelease(BufFreelistLock);
	return result;
}

/*
 * StrategyNotifyBgWriter -- set or clear allocation notification latch
 *
 * If bgwriterLatch isn't NULL, the next invocation of StrategyGetBuffer will
 * set that latch.	Pass NULL to clear the pending notification before it
 * happens.  This feature is used by the bgwriter process to wake itself up
 * from hibernation, and is not meant for anybody else to use.
 */
void
StrategyNotifyBgWriter(Latch *bgwriterLatch)
{
	/*
	 * We acquire the BufFreelistLock just to ensure that the store appears
	 * atomic to StrategyGetBuffer.  The bgwriter should call this rather
	 * infrequently, so there's no performance penalty from being safe.
	 */
	LWLockAcquire(BufFreelistLock, LW_EXCLUSIVE);
	StrategyControl->bgwriterLatch = bgwriterLatch;
	LWLockRelease(BufFreelistLock);
}


/*
 * StrategyShmemSize
 *
 * estimate the size of shared memory used by the freelist-related structures.
 *
 * Note: for somewhat historical reasons, the buffer lookup hashtable size
 * is also determined here.
 */
Size
StrategyShmemSize(void)
{
	Size		size = 0;

	/* size of lookup hash table ... see comment in StrategyInitialize */
	size = add_size(size, BufTableShmemSize(NBuffers + NUM_BUFFER_PARTITIONS));

	/* size of the shared replacement strategy control block */
	size = add_size(size, MAXALIGN(sizeof(BufferStrategyControl)));

	/* size of the LRU stack */
	size = add_size(size, mul_size(NBuffers, sizeof(StackNode)));

	return size;
}

/*
 * StrategyInitialize -- initialize the buffer cache replacement
 *		strategy.
 *
 * Assumes: All of the buffers are already built into a linked list.
 *		Only called by postmaster and only during initialization.
 */
void
StrategyInitialize(bool init)
{
	bool		found;
	int i = 0;
	/*
	 * Initialize the shared buffer lookup hashtable.
	 *
	 * Since we can't tolerate running out of lookup table entries, we must be
	 * sure to specify an adequate table size here.  The maximum steady-state
	 * usage is of course NBuffers entries, but BufferAlloc() tries to insert
	 * a new entry before deleting the old.  In principle this could be
	 * happening in each partition concurrently, so we could need as many as
	 * NBuffers + NUM_BUFFER_PARTITIONS entries.
	 */
	InitBufTable(NBuffers + NUM_BUFFER_PARTITIONS);

	/*
	 * Get or create the shared strategy control block
	 */
	StrategyControl = (BufferStrategyControl *)
		ShmemInitStruct("Buffer Strategy Status",
						sizeof(BufferStrategyControl) + NBuffers*sizeof(StackNode),
						&found);

	if (!found)
	{
		/*
		 * Only done once, usually in postmaster
		 */
		Assert(init);

		/*
		 * Grab the whole linked list of free buffers for our strategy. We
		 * assume it was previously set up by InitBufferPool().
		 */
		StrategyControl->firstFreeBuffer = 0;
		StrategyControl->lastFreeBuffer = NBuffers - 1;

		/* Initialize the clock sweep pointer */
		StrategyControl->nextVictimBuffer = 0;

		/* Clear statistics */
		StrategyControl->completePasses = 0;
		StrategyControl->numBufferAllocs = 0;

		/* No pending notification */
		StrategyControl->bgwriterLatch = NULL;

		// CS3223: initialize the LRU stack
		StrategyControl->size = 0;
		
		StrategyControl->tail = NOT_IN_STACK;
		StrategyControl->head = NOT_IN_STACK;
		StrategyControl->freePos = 0;
	}
	else
		Assert(!init);

	bool stack_found;
	LRUStack = (StackNode *) ShmemInitStruct("LRU stack", NBuffers * sizeof(StackNode), &stack_found);
	if(!stack_found)
	{
		/*
		* Only done once, usually in postmaster
		*/
		Assert(init);
		/*
		* initilize entries in LRU_Stack
		*/
		StackNode *iter = LRUStack;
		for (i=0;i<NBuffers;i++){
			iter->buf_id = NOT_IN_STACK;
			iter->next = NOT_IN_STACK;
			iter->prev = NOT_IN_STACK;
			iter++;
		}
	}
	else
		Assert(!init);

}


/* ----------------------------------------------------------------
 *				Backend-private buffer ring management
 * ----------------------------------------------------------------
 */


/*
 * GetAccessStrategy -- create a BufferAccessStrategy object
 *
 * The object is allocated in the current memory context.
 */
BufferAccessStrategy
GetAccessStrategy(BufferAccessStrategyType btype)
{
	BufferAccessStrategy strategy;
	int			ring_size;

	/*
	 * Select ring size to use.  See buffer/README for rationales.
	 *
	 * Note: if you change the ring size for BAS_BULKREAD, see also
	 * SYNC_SCAN_REPORT_INTERVAL in access/heap/syncscan.c.
	 */
	switch (btype)
	{
		case BAS_NORMAL:
			/* if someone asks for NORMAL, just give 'em a "default" object */
			return NULL;

		case BAS_BULKREAD:
			ring_size = 256 * 1024 / BLCKSZ;
			break;
		case BAS_BULKWRITE:
			ring_size = 16 * 1024 * 1024 / BLCKSZ;
			break;
		case BAS_VACUUM:
			ring_size = 256 * 1024 / BLCKSZ;
			break;

		default:
			elog(ERROR, "unrecognized buffer access strategy: %d",
				 (int) btype);
			return NULL;		/* keep compiler quiet */
	}

	/* Make sure ring isn't an undue fraction of shared buffers */
	ring_size = Min(NBuffers / 8, ring_size);

	/* Allocate the object and initialize all elements to zeroes */
	strategy = (BufferAccessStrategy)
		palloc0(offsetof(BufferAccessStrategyData, buffers) +
				ring_size * sizeof(Buffer));

	/* Set fields that don't start out zero */
	strategy->btype = btype;
	strategy->ring_size = ring_size;

	return strategy;
}

/*
 * FreeAccessStrategy -- release a BufferAccessStrategy object
 *
 * A simple pfree would do at the moment, but we would prefer that callers
 * don't assume that much about the representation of BufferAccessStrategy.
 */
void
FreeAccessStrategy(BufferAccessStrategy strategy)
{
	/* don't crash if called on a "default" strategy */
	if (strategy != NULL)
		pfree(strategy);
}

/*
 * GetBufferFromRing -- returns a buffer from the ring, or NULL if the
 *		ring is empty.
 *
 * The bufhdr spin lock is held on the returned buffer.
 */
static volatile BufferDesc *
GetBufferFromRing(BufferAccessStrategy strategy)
{
	volatile BufferDesc *buf;
	Buffer		bufnum;

	/* Advance to next ring slot */
	if (++strategy->current >= strategy->ring_size)
		strategy->current = 0;

	/*
	 * If the slot hasn't been filled yet, tell the caller to allocate a new
	 * buffer with the normal allocation strategy.	He will then fill this
	 * slot by calling AddBufferToRing with the new buffer.
	 */
	bufnum = strategy->buffers[strategy->current];
	if (bufnum == InvalidBuffer)
	{
		strategy->current_was_in_ring = false;
		return NULL;
	}

	/*
	 * If the buffer is pinned we cannot use it under any circumstances.
	 *
	 * If usage_count is 0 or 1 then the buffer is fair game (we expect 1,
	 * since our own previous usage of the ring element would have left it
	 * there, but it might've been decremented by clock sweep since then). A
	 * higher usage_count indicates someone else has touched the buffer, so we
	 * shouldn't re-use it.
	 */
	buf = &BufferDescriptors[bufnum - 1];
	LockBufHdr(buf);
	if (buf->refcount == 0 && buf->usage_count <= 1)
	{
		strategy->current_was_in_ring = true;
		return buf;
	}
	UnlockBufHdr(buf);

	/*
	 * Tell caller to allocate a new buffer with the normal allocation
	 * strategy.  He'll then replace this ring element via AddBufferToRing.
	 */
	strategy->current_was_in_ring = false;
	return NULL;
}

/*
 * AddBufferToRing -- add a buffer to the buffer ring
 *
 * Caller must hold the buffer header spinlock on the buffer.  Since this
 * is called with the spinlock held, it had better be quite cheap.
 */
static void
AddBufferToRing(BufferAccessStrategy strategy, volatile BufferDesc *buf)
{
	strategy->buffers[strategy->current] = BufferDescriptorGetBuffer(buf);
}

/*
 * StrategyRejectBuffer -- consider rejecting a dirty buffer
 *
 * When a nondefault strategy is used, the buffer manager calls this function
 * when it turns out that the buffer selected by StrategyGetBuffer needs to
 * be written out and doing so would require flushing WAL too.	This gives us
 * a chance to choose a different victim.
 *
 * Returns true if buffer manager should ask for a new victim, and false
 * if this buffer should be written and re-used.
 */
bool
StrategyRejectBuffer(BufferAccessStrategy strategy, volatile BufferDesc *buf)
{
	/* We only do this in bulkread mode */
	if (strategy->btype != BAS_BULKREAD)
		return false;

	/* Don't muck with behavior of normal buffer-replacement strategy */
	if (!strategy->current_was_in_ring ||
	  strategy->buffers[strategy->current] != BufferDescriptorGetBuffer(buf))
		return false;

	/*
	 * Remove the dirty buffer from the ring; necessary to prevent infinite
	 * loop if all ring members are dirty.
	 */
	strategy->buffers[strategy->current] = InvalidBuffer;

	return true;
}

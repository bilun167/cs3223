
#include "postgres.h"
#include "storage/buf_internals.h"
#include "stubs.h"


MemoryContext CurrentMemoryContext = NULL;


void SetLatch(volatile Latch *latch)
{
}

void * palloc0(Size size)
{
	return 0;
}


void *
MemoryContextAllocZero(MemoryContext context, Size size)
{
	return 0;
}

int
s_lock(volatile slock_t *lock, const char *file, int line)
{
	return 0;
}

void
InitBufTable(int size)
{

}


Size
BufTableShmemSize(int size)
{
	return 0;
}

Size
add_size(Size s1, Size s2)
{
	return 0;
}

extern int NBuffers;
//extern bool assert_enabled = true;

// ******************************
// src/backend/utils/error/elog.c
// ******************************
ErrorContextCallback *error_context_stack = NULL;

void
elog_start(const char *filename, int lineno, const char *funcname) {

}

void
elog_finish(int elevel, const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
	exit(1);
}

// ******************************
// src/backend/storage/lmgr/lwlock.c
// ******************************

LWLockId LWLockAssign(void) {
	return 0;
}

void LWLockAcquire(LWLockId lockid, LWLockMode mode){

}

void
LWLockRelease(LWLockId lockid)
{

}

/*
void
ProcSendSignal(BackendId procId) {
}
*/

void *MemoryContextAlloc(MemoryContext context, Size size) {
	return malloc(size);
}

void pfree(void *pointer) {
	free(pointer);
}

void *
ShmemInitStruct(const char *name, Size size, bool *foundPtr)
{
	*foundPtr = false;
	return malloc(size);
}

// ******************************
// src/backend/storage/ipc/shmem.c
// ******************************


Size
mul_size(Size s1, Size s2)
{
	return 0;
}

// ******************************
// src/backend/storage/buffer/buf_init.c
// ******************************

long	*PrivateRefCount;

BufferDesc *BufferDescriptors;

char	*BufferBlocks;

void
InitBufferPool () {

	int	i;

	PrivateRefCount = (long *) malloc(NBuffers * sizeof(long));

	// Altered to use regular memory
	BufferDescriptors = (BufferDesc *) malloc (NBuffers * sizeof(BufferDesc));
    BufferBlocks = (char *) malloc (NBuffers * BLCKSZ);

	ShmemBase = BufferBlocks;
	// ShmemBase = (unsigned long) BufferBlocks;

	if (false)
	{
	}
	else
	{
		BufferDesc *buf;
		buf = BufferDescriptors;

		for (i = 0; i < NBuffers; buf++, i++)
		{
			CLEAR_BUFFERTAG(buf->tag);
			buf->flags    = 0;
			buf->usage_count = 0;
			buf->refcount = 0;
			buf->wait_backend_pid = 0;
			buf->freeNext = i + 1;
			buf->buf_id = i;

			*((char *) MAKE_PTR(i * BLCKSZ)) = '#';

			buf->io_in_progress_lock = LWLockAssign();
			buf->content_lock = LWLockAssign();
		}

		/* close the circular queue */
                BufferDescriptors[NBuffers - 1].freeNext = -1;
		StrategyInitialize(true);
	}

}



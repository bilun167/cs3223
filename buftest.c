/*
 * SIMPLE Buffer Tester
 *
*/

#include "postgres.h"
#include "storage/buf_internals.h"
#include "storage/bufmgr.h"
#include "stubs.h"

void* ShmemBase;

int NBuffers;
#undef INIT_BUFFERTAG
#define INIT_BUFFERTAG(a,r,b) \
( \
	(a).rnode.spcNode = (a).rnode.dbNode = 0, \
	(a).rnode.relNode = (r), \
	(a).blockNum = (b) \
)

extern void StrategyUpdateAccessedBuffer(int buf_id, bool samepage);

void
printBuffers() {
	int i;
	BufferDesc *buf;

	buf = BufferDescriptors;

	for (i=0; i<NBuffers; buf++, i++) {
	  if (buf->refcount == 0) {
		   printf("[%1s]",((char *) MAKE_PTR(i * BLCKSZ)));
	  }
		else {
		  printf("(%1s)",((char *) MAKE_PTR(i * BLCKSZ)));
		}
	}
	printf("\n");
}

volatile BufferDesc*
findPage(BufferTag *btag, bool adjust) {

		int			i;
        BufferDesc *buf;
		BufferTag  *oldtag;

		for(i = 0; i < NBuffers; i++){

			buf = &BufferDescriptors[i];
			oldtag = &(buf->tag);

			if(btag->rnode.relNode == oldtag->rnode.relNode &&
			   btag->blockNum == oldtag->blockNum)
			{
				if(adjust)
					StrategyUpdateAccessedBuffer(i, true);
				return buf;
			}
		}

		return NULL;
}

void
writePage(char pg, volatile BufferDesc *buf) {
        *((char *) MAKE_PTR(buf->buf_id * BLCKSZ)) = pg;
}

volatile BufferDesc *
getPage(Oid rel, int bno) {
	BufferTag  btag;
    volatile BufferDesc *buf;
	bool	lock_held;

	INIT_BUFFERTAG(btag, rel, bno);

        // Find page if in memory
        buf = findPage(&btag, true);
        if (buf == NULL) {
            // Get a free page
            buf = StrategyGetBuffer(NULL, &lock_held); //this is the LRU main code

			if (buf == NULL) {
				printf("Out of buffers!\n");
				exit(0);
			}
			else if (buf->refcount > 0) {
				printf("Pinned buffer!\n");
				exit(0);
			}


			buf->refcount = 1;
			PrivateRefCount[BufferDescriptorGetBuffer(buf) - 1] = 1;
        }
		else {
			buf->refcount++;
			PrivateRefCount[BufferDescriptorGetBuffer(buf) - 1]++;
			return buf;
		}

		buf->tag = btag;
		return buf;
}

void
unpinPage(Oid rel, int bno) {
	BufferTag  btag;
	volatile BufferDesc *buf;

	INIT_BUFFERTAG(btag, rel, bno);
	buf = findPage(&btag, false);

        if (buf == NULL)
		printf("Page not in memory!\n");
        else {
		buf->refcount--;
		PrivateRefCount[BufferDescriptorGetBuffer(buf) - 1]--;
        }
}

#define GET_WRITE(r, b, v) GET_WRITE_PIN(r, b, v, false)

#define GET_WRITE_PIN(r, b, v, p) \
do { \
	volatile BufferDesc *bdesc; \
	bdesc = getPage((r), (b)); \
	writePage((v), bdesc); \
	if (!(p)) unpinPage((r), (b)); \
} while (0)

int
main(int argc, char *argv[]) {
#include "testcase.c"

	printf("Finished.\n");
	return 0;
}

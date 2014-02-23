CPP=gcc
OPTS= -Wall
#OPTS=-g -Wall
LIBS=-lresolv -ldl -lm
# Modify PSQLPATH if necesssary
#PSQLPATH=/home/alice/postgresql-9.3.2
PSQLPATH=/home/sadm/postgresql-9.3.2
INCLUDE=-I$(PSQLPATH)/src/include     
all: buftest

stubs.o: stubs.c
	$(CPP) $(OPTS) $(INCLUDE) -c -o stubs.o stubs.c

freelist-lru.o: freelist-lru.c
	$(CPP) $(OPTS) $(INCLUDE) -c -o freelist-lru.o freelist-lru.c

buftest: buftest.c stubs.o freelist-lru.o testcase.c
	$(CPP) $(OPTS) $(LIBS) $(INCLUDE) -o buftest buftest.c stubs.o freelist-lru.o

freelist-lru2.o: freelist-lru2.c
	$(CPP) $(OPTS) $(INCLUDE) -c -o freelist-lru2.o freelist-lru2.c

buftest2: buftest.c stubs.o freelist-lru2.o testcase.c
	$(CPP) $(OPTS) $(LIBS) $(INCLUDE) -o buftest2 buftest.c stubs.o freelist-lru2.o

clean:
	rm -f *.o
	rm -f buftest
	rm -f buftest2

# building postgresql

lru: copylru pgsql

lru2: copylru2 pgsql

clock: copyclock pgsql

copylru:
	cp freelist-lru.c $(PSQLPATH)/src/backend/storage/buffer/freelist.c
	cp bufmgr.c $(PSQLPATH)/src/backend/storage/buffer/bufmgr.c

copylru2:
	cp freelist-lru2.c $(PSQLPATH)/src/backend/storage/buffer/freelist.c
	cp bufmgr.c $(PSQLPATH)/src/backend/storage/buffer/bufmgr.c

copyclock:
	cp freelist.original.c $(PSQLPATH)/src/backend/storage/buffer/freelist.c
	cp bufmgr.original.c $(PSQLPATH)/src/backend/storage/buffer/bufmgr.c

pgsql:
	cd $(PSQLPATH) && make && make install


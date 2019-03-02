CC=clang
CFLAGS=-I. -g

all: mutex.o test thread-test

clean:
	rm -f *.o test thread-test

mutex.o: mutex.c
	$(CC) -o mutex.o -c mutex.c $(CFLAGS)

test: mutex.c test.c
	$(CC) -o test mutex.c test.c $(CFLAGS) -D_UNIT_TEST=1

thread-test: mutex.c thread-test.c
	$(CC) -o thread-test mutex.c thread-test.c $(CFLAGS) -lpthread

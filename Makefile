CC=/usr/local/Cellar/gcc/7.2.0/bin/gcc-7
CFLAGS=-I. -g

all: mutex.o mutex-test mutex-thread-test

clean:
	rm -f *.o mutex-test mutex-thread-test

mutex.o: mutex.c
	$(CC) -o mutex.o -c mutex.c $(CFLAGS)

mutex-test: mutex.c mutex-test.c
	$(CC) -o mutex-test mutex.c mutex-test.c $(CFLAGS) -D_UNIT_TEST=1

mutex-thread-test: mutex.c mutex-thread-test.c
	$(CC) -o mutex-thread-test mutex.c mutex-thread-test.c $(CFLAGS) -lpthread

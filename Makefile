CC=/usr/local/Cellar/gcc/7.2.0/bin/gcc-7
CFLAGS=-I. -g

mutex.o: mutex.c
	$(CC) -o mutex.o -c mutex.c $(CFLAGS)

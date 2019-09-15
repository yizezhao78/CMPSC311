CC := gcc
CFLAGS := -Wall -Wuninitialized -O
PROGS := main

.PHONY:all

all: $(PROGS)

main: main.o list.o mymalloc.o
	$(CC) $(CFLAGS) -Wl,--wrap,malloc -Wl,--wrap,free -o $@ main.o list.o mymalloc.o

mymalloc.o:
	$(CC) $(CFLAGS) -DLINKTIME -c mymalloc.c

main.o: list.h
list.o: list.h

.PHONY:clean

clean:
	rm -f $(PROGS) *.o

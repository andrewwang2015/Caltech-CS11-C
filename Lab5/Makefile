#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: 1dcaPointers 1dcaArrays

1dcaPointers: 1dcaPointers.o memcheck.o
	$(CC) 1dcaPointers.o memcheck.o -o 1dcaPointers

1dcaArrays: 1dcaArrays.o memcheck.o
	$(CC) 1dcaArrays.o memcheck.o -o 1dcaArrays

1dcaArrays.o: 1dcaArrays.c memcheck.h
	$(CC) $(CFLAGS) -c 1dcaArrays.c

1dcaPointers.o: 1dcaPointers.c memcheck.h
	$(CC) $(CFLAGS) -c 1dcaPointers.c

memcheck.o: memcheck.c
	$(CC) $(CFLAGS) -c memcheck.c 

check:
	c_style_check 1dcaPointers.c 1dcaArrays.c

clean:
	rm -f *.o 1dcaPointers 1dcaArrays memcheck




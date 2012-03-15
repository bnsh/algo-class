CC=g++
CFLAGS=-g3 -O2 -Wall -Werror

all: q1

q1: q1.o
	$(CC) $(CFLAGS) $(^) -o $(@)

q1.o: q1.C
	$(CC) -c $(CFLAGS) $(^) -o $(@)


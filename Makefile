CC = gcc
CFLAGS = -Wall -c -g
LDFLAGS = -lm

all: a.out

a.out: calc.o truth_table.o list.o
		$(CC) calc.o truth_table.o list.o $(LDFLAGS) -o a.out

calc.o: calc.c truth_table.h
		$(CC) $(CFLAGS) calc.c

truth_table.o: truth_table.c truth_table.h list.h
		$(CC) $(CFLAGS) truth_table.c

list.o: list.c list.h
		$(CC) $(CFLAGS) list.c

clean:
		rm -f *.o a.out


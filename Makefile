CC = gcc
CFLAGS = -Wall -c -g
LDFLAGS = -lm

all: a.out

a.out: calc.o truth_table.o
		$(CC) calc.o truth_table.o $(LDFLAGS) -o a.out

calc.o: calc.c truth_table.h
		$(CC) $(CFLAGS) calc.c

truth_table.o: truth_table.c truth_table.h
		$(CC) $(CFLAGS) truth_table.c

clean:
		rm -f *.o a.out


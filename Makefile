CC = gcc
CFLAGS = -Wall -c -g
LDFLAGS = -lm

all: a.out

a.out: main.o truth_table.o
		$(CC) main.o truth_table.o $(LDFLAGS) -o a.out

calculator.o: main.c truth_table.h
		$(CC) $(CFLAGS) main.c

truth_table.o: truth_table.c truth_table.h
		$(CC) $(CFLAGS) truth_table.c

clean:
		rm -f *.o a.out


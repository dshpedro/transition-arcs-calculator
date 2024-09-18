CC = gcc
CFLAGS = -Wall -c -g
LDFLAGS = -lm

all: a.out

a.out: calculator.o truth_table.o
		$(CC) calculator.o truth_table.o $(LDFLAGS) -o a.out

calculator.o: calculator.c truth_table.h
		$(CC) $(CFLAGS) calculator.c

truth_table.o: truth_table.c truth_table.h
		$(CC) $(CFLAGS) truth_table.c

clean:
		rm -f *.o a.out


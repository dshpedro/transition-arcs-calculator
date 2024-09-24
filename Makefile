CC = gcc
CFLAGS = -Wall -c -g
LDFLAGS = -lm

all: a.out

a.out: main.o truth_table.o utils.o
		$(CC) main.o truth_table.o utils.o $(LDFLAGS) -o a.out

main.o: main.c truth_table.h utils.h
		$(CC) $(CFLAGS) main.c

truth_table.o: truth_table.c truth_table.h
		$(CC) $(CFLAGS) truth_table.c

utils.o: utils.c utils.h
		$(CC) $(CFLAGS) utils.c

clean:
		rm -f *.o a.out


CC = gcc
CFLAGS = -Wall -c
LDFLAGS = -lm
TARGET = arcs.out

all: $(TARGET)

debug: CFLAGS += -g
debug: $(TARGET)

$(TARGET): main.o calculator.o list.o truth_table.o utils.o
		$(CC) main.o calculator.o list.o truth_table.o utils.o $(LDFLAGS) -o $(TARGET)

calculator.o: calculator.c calculator.h list.h truth_table.h
		$(CC) $(CFLAGS) calculator.c

list.o: list.c list.h
		$(CC) $(CFLAGS) list.c

main.o: main.c calculator.h list.h truth_table.h utils.h
		$(CC) $(CFLAGS) main.c

truth_table.o: truth_table.c truth_table.h
		$(CC) $(CFLAGS) truth_table.c

utils.o: utils.c utils.h
		$(CC) $(CFLAGS) utils.c

clean:
		rm -f *.o *.out


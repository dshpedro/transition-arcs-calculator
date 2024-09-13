#include "list.h"

typedef struct Row {
    List *values;
    struct Row *next;
} Row;

typedef struct {
    Row *first_row;
    int rows;
    int columns;
} Truth_table;

Row *new_row();
Truth_table *new_truth_table(int rows, int columns);
void print_row(Row *row);
void print_truth_table(Truth_table *tb);


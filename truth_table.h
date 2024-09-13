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

bool get_lsb(int decimal, int shift_ammount);
Row *new_row();
Truth_table *new_truth_table(int rows, int columns);
void populate_row(Row *row, int decimal, int n);
void populate_table(Truth_table *tb);
void print_row(Row *row);
void print_truth_table(Truth_table *tb);


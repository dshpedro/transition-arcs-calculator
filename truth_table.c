#include "truth_table.h"
#include <stdlib.h>
#include <stdio.h>

Row *new_row() {
    Row *row = malloc(sizeof *row);
    row->values = new_list();
    row->next = NULL;
    return row;
}

Truth_table *new_truth_table(int rows, int columns) {
    Truth_table *tb = malloc(sizeof *tb);
    tb->first_row = new_row();
    tb->rows = rows;
    tb->columns = columns;
    return tb;
}

void print_row(Row *row) {
    print_list(row->values);
}

void print_truth_table(Truth_table *tb) {
    Row *curr_row = tb->first_row;
    while(curr_row != NULL) {
        print_row(curr_row);
        curr_row = curr_row->next;
    }
}


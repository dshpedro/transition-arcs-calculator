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
    tb->row_0 = new_row();
    tb->rows = 0;
    tb->columns = 0;
    return tb;
}

void print_row(Row *row) {
    while(row != NULL) {
        print_list(row->values);
        row = row->next;
    }
}

void print_truth_table(Truth_table *tb) {
    int rows = tb->rows;
    
    printf("A B C\n");
    Row *curr_row = tb->row_0;
    while(curr_row != NULL) {
        print_row(curr_row);
        curr_row = curr_row->next;
    }
}


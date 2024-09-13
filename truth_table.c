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
    populate_table(tb);
    return tb;
}

void populate_row(Row *row, int counter, int n) {
    bool lsb = false;
    for(int i = 0; i < n; i++) {
        insert_at_start(row->values, lsb);
    }
}

void populate_table(Truth_table *tb) {
    Row *curr_row = tb->first_row;
    Row *aux_row;
    int counter = 0;
    for(int i = 0; i < tb->rows ; i++) {
        populate_row(curr_row, counter, tb->columns);
        aux_row = new_row();
        curr_row->next = aux_row;
        curr_row = aux_row;
    }
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


#include "truth_table.h"
#include <stdlib.h>


Row *new_row() {
    Row *row = malloc(sizeof *row);
    row->values = new_list();
    row->next = NULL;
    return row;
}

Truth_table *new_truth_table() {
    Truth_table *tb = malloc(sizeof *tb);
    tb->row_0 = new_row();
    tb->rows = 0;
    tb->columns = 0;
    return tb;
}

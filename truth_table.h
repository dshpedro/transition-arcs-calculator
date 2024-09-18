#include <stdbool.h>

typedef struct {
    int n;
    int rows;
    char *variables;
    bool **table;
} Truth_table;

bool get_lsb(int decimal, int shift_ammount);
Truth_table *new_truth_table(char *variables);
void populate_table(Truth_table *tt);
void print_truth_table(Truth_table *tt);


#include <stdbool.h>

typedef struct {
    int n;
    int rows;
    char *variables;
    bool **table;
} Truth_table;

bool evaluate_expression(Truth_table *tt, int row, char *expression);
void evaluate_table(Truth_table *tt, int argc, char *argv[]);
int get_index_of_var(char var, Truth_table *tt);
bool get_lsb(int decimal, int shift_ammount);
Truth_table *new_truth_table(char *variables);
void populate_table(Truth_table *tt);
void print_truth_table(Truth_table *tt);


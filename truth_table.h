#include <stdbool.h>

typedef struct {
    int amount_of_variables;
    int amount_of_rows;
    char *expression;
    char *variables;
    bool **table;
} Truth_table;

bool evaluate_minterm(Truth_table *tt, int row, char *minterm);
void evaluate_table(Truth_table *tt);
int get_index_of_var(Truth_table *tt, char var);
bool get_lsb(int decimal, int shift_ammount);
char **get_minterms(char *expression);
Truth_table *new_truth_table(char *variables, char *expression);
void populate_table(Truth_table *tt);

void print_minterms(Truth_table *tt);
void print_truth_table(Truth_table *tt);


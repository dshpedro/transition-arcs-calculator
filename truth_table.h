#include <stdbool.h>

typedef struct {
    int n;
    int rows;
    char *expression;
    char *variables;
    bool **table;
} Truth_table;

bool evaluate_expression(Truth_table *tt, int row, char *expression);
void evaluate_table(Truth_table *tt);
int get_index_of_var(Truth_table *tt, char var);
bool get_lsb(int decimal, int shift_ammount);
Truth_table *new_truth_table(char *variables, char *expression);
void populate_table(Truth_table *tt);
void print_truth_table(Truth_table *tt);
char **tokenize_expression(char *expression);


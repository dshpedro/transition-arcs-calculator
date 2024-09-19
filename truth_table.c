#include "truth_table.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool not(Truth_table *tt, int row, bool result, char *expression, int index) {
    /* Assuming all input expressions are on the correct format
     * every '!' will be succeded by a variable, therefore we can evaluate
     * this variable and move 2 positions foward from the '!' operator
     */
    result = result &&
             !tt->table[row][get_index_of_var(expression[index], tt)];
    return result;
}

bool evaluate_expression(Truth_table *tt, int row, char *expression) {

    bool result = true; 
    int length = strlen(expression);
    for(int i = 0; i < length; i++) {
        switch (expression[i]) {
            case '!':
                i++;
                result = not(tt, row, result, expression, i);
                break;
            case '*':
                // add something here
                break;
            default:
                if(islower(expression[i])) {
                    char var1 = expression[i];
                    i++; // has '*' 
                    i++; // has the second var
                    char var2 = expression[i];
                    result = result && 
                             tt->table[row][get_index_of_var(var1, tt)] &&
                             tt->table[row][get_index_of_var(var2, tt)];
                }
        }
        // if a subexpression among ANDs is false
        // the final result will also be false
        if(result == false)
            return false;
    }

    return result;
}

void evaluate_table(Truth_table *tt, int argc, char *argv[]) {
    /* Assuming an input expression with argc == 4, that correctly follows
     * the input format rules specified, we can conclude the following:
     * argv[0] contains the program's name
     *
     * argv[1] contains an expression with ! and/or * operators
     * argv[2] contains a single + operator 
     * argv[3] contains an expression with ! and/or * operators
     * 
     * therefore we can evaluate each subexpression separatly
     * if we find one that is true, there's no need to check the rest
     * in that row, since the whole will be true
     */
    for(int row = 0; row < tt->rows; row++) {
        for(int i = 1; i < argc; i++) {
            if(evaluate_expression(tt, row, argv[i])) {
                tt->table[row][tt->n] = true;
                break;
            }
        }
    }
}

int get_index_of_var(char var, Truth_table *tt) {
    /* strchr returns a pointer to the first appearance of
     * var, subtracting it from the pointer to the start
     * yields the correct index of var
     */
    char *var_pointer = strchr(tt->variables, var);
    if(var_pointer != NULL)
        return var_pointer - tt->variables;
    else
        return -1;
}

bool get_lsb(int decimal, int shift_ammount) {
    /* receives a decimal number and the ammount to shift it
     * returns the LSB of it's binary version
     */
    return (decimal >> shift_ammount) & 1;
}

Truth_table *new_truth_table(char *variables) {
    Truth_table *tt = malloc(sizeof *tt);
    int n = strlen(variables);
    
    tt->n = n;
    tt->rows = pow(2, n);
    tt->variables = variables;
    
    /* the mallocs below could be moved to populate_table
     * to eliminate an extra 2^n loop
     */
    tt->table = malloc(tt->rows * sizeof(bool *));
    for(int i = 0; i < tt->rows; i++)
        tt->table[i] = malloc((n+1) *sizeof(bool));

    populate_table(tt);
    return tt;
}

void populate_table(Truth_table *tt) {
    // dec == decimal
    for(int dec = 0; dec < tt->rows; dec++) {
        for(int i = 0; i < tt->n; i++) {
            tt->table[dec][(tt->n - 1) - i] = get_lsb(dec, i);
        }
        tt->table[dec][tt->n] = false; // defaults the S (result) to false
    }
}

void print_truth_table(Truth_table *tt) {
    printf("%sS\n", tt->variables);
    for(int i = 0; i < tt->rows; i++) {
        for(int j = 0; j <= tt->n; j++) {
            if(tt->table[i][j])
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}


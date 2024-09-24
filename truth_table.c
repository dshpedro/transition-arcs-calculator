#include "truth_table.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool evaluate_expression(Truth_table *tt, int row, char *expression) {
    /* We can separate the evaluation in different parts/cases, since
     * the expression can start with either a ! or a lowercase letter
     * we have:
     * part 1: evaluate the NOT or value of the variable in the truth table,
     * therefore this part has 2 cases '!' and 'islower'
     *
     * part 2: we can then search for an '*' operator to make an AND with the
     * previous result. This part will have 2 cases aswell, we can either find
     * a lowercase letter or a '!' operator after the '*'
     */
    bool result = true; 
    int i = 0;
    char var;
    int var_index;

    // Part 1
    if(*expression == '!') { // Case 1
        var = expression[++i]; // after ! there should be a lowercase letter, a variable
        var_index = get_index_of_var(tt, var);
        result = result && !tt->table[row][var_index];
    }
    else if (islower(*expression)) { // Case 2
        var = expression[i];
        var_index = get_index_of_var(tt, var);
        result = result && tt->table[row][var_index];
    }
    // for the current i, expression[i] contains a lowercase letter
    
    // Part 2
    i++; // now expression[i] contains an '*'
    int length = strlen(expression);
    while(i < length) {
        /* if a subexpression among ANDs is false
         * then the final result will also be false
         */
        if(result == false)
            return false;
      
        i++; // expression[i] is now either '!' or a lowercase letter
        if(expression[i] == '!') { // Case 1
            // after ! there should be a lowercase letter, a variable
            var = expression[++i]; 
            var_index = get_index_of_var(tt, var);
            result = result && !tt->table[row][var_index];
        }
        else if(islower(expression[i])) { // Case 2
            var = expression[i];
            var_index = get_index_of_var(tt, var);
            result = result && tt->table[row][var_index];
        }
        // for the current i, expression[i] contains a lowercase letter

      i++; // expression[i] is now an '*'
    }

    return result;
}

void evaluate_table(Truth_table *tt) {
    /* This function will evaluate the table row per row.
     * To take advantage from the SOP format of the input expression
     * we will evaluate break the whole expression into minsters and
     * evaluate each one separatly, if we find one that is true, there's 
     * no need to check the rest in that row, since infer the whole will be true
     */
    char **expressions = get_minterms(tt->expression);
    int n = 0; // ammount of minterms;
    while(expressions[n] != NULL)
        n++;
    
    // debug info, prints the minterms
    printf("SOP Minterms:\n");
    for(int i = 0; i < n; i++) 
        printf("%d: %s\n", i, expressions[i]);
    printf("\n");

    char *minterm;
    for(int row = 0; row < tt->rows; row++) {
        for(int i = 0; i < n; i++) {
            minterm = expressions[i];
            if(evaluate_expression(tt, row, minterm)) {
                tt->table[row][tt->n] = true;
                break;
            }
        }
    }
}

int get_index_of_var(Truth_table *tt, char var) {
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

Truth_table *new_truth_table(char *variables, char *expression) {
    Truth_table *tt = malloc(sizeof *tt);
    int n = strlen(variables);
    
    tt->n = n;
    tt->rows = pow(2, n);
    tt->variables = variables;
    tt->expression = expression;
    
    /* the mallocs below could be moved to populate_table
     * to eliminate an extra 2^n loop
     */
    tt->table = malloc(tt->rows * sizeof(bool *));
    for(int i = 0; i < tt->rows; i++)
        tt->table[i] = malloc((n+1) *sizeof(bool));

    populate_table(tt);
    evaluate_table(tt);
    return tt;
}

char **get_minterms(char *expression) {
    /* Tokenizes the SOP expression into it's minterms,
     * subexpressions with only ANDs and NOTs
     *
     * assumes there's atleast one minterm, aka, the expression itself
     * this also accounts for adding one more minterm than there
     * are + operators, e.g., 'a + b', there's 1 + operator but 2 minterms 
     */
    char *expression_copy = strdup(expression);
    int token_count = 1; 
    while(*expression != '\0') {
        if(*expression++ == '+')
            token_count++;
    }

    char **minterms = malloc((token_count + 1) * sizeof (char *));
    minterms[token_count] = NULL;
    if(token_count == 1) {
        minterms[0] = strdup(expression_copy);
        free(expression_copy);
        return minterms;
    }
    
    // any combination of ' ' and '+' will be considered a delimiter
    char *delim = " +"; 
    char *token = strtok(expression_copy, delim);
    for(int i = 0; i < token_count; i++) {
        minterms[i] = strdup(token);
        token = strtok(NULL, delim);
    }
    free(expression_copy);

    return minterms;
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
    printf("Truth table:\n");
    printf("%s|S\n", tt->variables);
    for(int i = 0; i < tt->rows; i++) {
        for(int j = 0; j < tt->n; j++) {
            if(tt->table[i][j])
                printf("1");
            else
                printf("0");
        }
        // print result (S)
        if(tt->table[i][tt->n])
            printf("|1\n");
        else
            printf("|0\n");
    }
}


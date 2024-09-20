#include "truth_table.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool not(Truth_table *tt, int row, char var) {
    /* Assuming all input expressions are on the correct format
     * every '!' will be succeded by a variable, therefore we can evaluate
     * this variable and move 2 positions foward from the '!' operator
     */
    int i = get_index_of_var(tt, var);
    bool result = !tt->table[row][i];
    return result;
}

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
    char **expressions = tokenize_expression(tt->expression);
    int n = 0; // ammount of subexpressions
    while(expressions[n] != NULL)
        n++;
    for(int i = 0; i < n; i++) // debug info, prints the minterms
        printf("%d: %s\n", i, expressions[i]);

    char *subexpression;
    for(int row = 0; row < tt->rows; row++) {
        for(int i = 0; i < n; i++) {
            subexpression = expressions[i];
            if(evaluate_expression(tt, row, subexpression)) {
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

char *remove_spaces(char *string) {
    int not_spaces = 0;
    char *aux = string;
    while(*aux != '\0') {
        if(*aux != ' ')
            not_spaces++;
        aux++;
    }
    
    char *new = malloc(not_spaces + 1);
    aux = new;
    while(*string != '\0') {
        if(*string != ' ')
            *aux++ = *string;
        string++;
    }
    *aux= '\0';

    return new;
}

char **tokenize_expression(char *expression) {
    /* Tokenizes SOPs expressions into subexpressions with ANDs and NOTs
     *
     * assumes there's atleast one subexpression, aka, the expression itself
     * this also accounts for adding one more subexpression than there
     * are + operators, e.g., 'a + b', there's 1 + operator but 2 subexpressions
     */
    char *expression_copy = strdup(expression);
    remove_spaces(expression_copy);
    int token_count = 1; 
    while(*expression != '\0') {
        if(*expression++ == '+')
            token_count++;
    }

    char **tokens = malloc((token_count + 1) * sizeof (char *));
    tokens[token_count] = NULL;
    if(token_count == 1) {
        tokens[0] = strdup(expression_copy);
        free(expression_copy);
        return tokens;
    }
    
    char *token = strtok(expression_copy, " + ");
    for(int i = 0; i < token_count; i++) {
        tokens[i] = strdup(token);
        token = strtok(NULL, " + ");
    }
    free(expression_copy);

    return tokens;
}


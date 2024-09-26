#include "calculator.h"
#include "utils.h"
#include <stdlib.h>

List *calculate_arcs(Truth_table *tt) {
    /* To understand how this function works let's first take a look at 
     * the truth table for 'a*b + !a*c':
     *
     * abc|S
     * 000|0        * 000
     * 001|1
     * 010|0
     * 011|1
     * 100|0        * 100
     * 101|0
     * 110|1
     * 111|1
     *
     * Characteristics and patterns we can observe:
     *    It has 3 variables, we can represent that with n = 3
     *    For simplicity's sake, let's refer to these as variable 0, 1 and 2:
     *    tt->variables[0] = 'a'
     *    tt->variables[1] = 'b'
     *    tt->variables[2] = 'c'
     *
     *    The lines with asterisks highlight 2 numbers with the hamming distance of 1.
     *    If they also differ in their S value they can be called a transition arc.
     
     *    Amount of consecutive lines with 0's
     *    variables[0] has 4 lines with consecutive 0's
     *    variables[1] has 2 lines with consecutive 0's
     *    variables[2] has 1 line with 'consecutive' 0
     *
     *    We can infer the rule for consecutives lines with 0 as:
     *        2^(n-1-variable_index).
     *    Using n-1 = 2:
     *        2^(2-0) = 2^2 = 4
     *        2^(2-1) = 2^1 = 2
     *        2^(2-2) = 2^0 = 1
     *
     * This function will iterate trough each variable, focusing on the lines where
     * it's value is 0, and compare it with it's pair of Hamming distance 1.
     */
    List *arcs = new_list();
    insert_at_end(arcs, "Transition Arcs:");

    // characteristics discussed at the top comment
    int consecutives;                // number of consecutives 0's
    int first_hamming_pair;          // hamming distance of 1
    int n = tt->amount_of_variables; // n is also the result column

    // checks every possible arc for each variable
    for(int var_index = 0; var_index < n; var_index++) {
        consecutives = pow(2, (n-1) - var_index);
        first_hamming_pair = consecutives;

        int amount_of_rows = tt->amount_of_rows;
        for(int row = 0; row < amount_of_rows; row++) {
            if(tt->table[row][var_index] == 0) {
                if(tt->table[row][n] != tt->table[first_hamming_pair + row][n])
                    insert_at_end(arcs, get_arc_string(tt, row, var_index));
            }
            else
                row += consecutives - 1;
        }
    }
  
    return arcs;
}

char *get_arc_string(Truth_table *tt, int row, int var_index) {
    int n = tt->amount_of_variables;
    char *arc_string = malloc(n);

    for(int i = 0; i < n; i++) {
        if(i == var_index)
            arc_string[i] = tt->variables[var_index];
        else
            arc_string[i] = bool_to_char(tt->table[row][i]);
    }

    return arc_string;
}


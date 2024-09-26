#include "calculator.h"
#include "utils.h"
#include <stdlib.h>

List *calculate_arcs(Truth_table *tt) {
    /* To gather the fundamentals to understand how this function works let's first 
     * take a look at the truth table for 'a*b + !a*c':
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
     * Characteristics and patterns we can find:
     *    It has 3 variables, we can represent that with n = 3
     *    For simplicity's sake, let's refer to these as variable 0, 1 and 2:
     *    tt->variables[0] = 'a'
     *    tt->variables[1] = 'b'
     *    tt->variables[2] = 'c'
     *
     *    The lines with asterisks highlight 2 numbers with the hamming distance of 1.
     *    These lines are the ones that can possibly harbor a transition arc depending 
     *    on the result of each one, that is, if they also differ in their S value, then
     *    they are considered a transition arc.
     *
     *    variables[0] has 1 occurrence of 4 lines with consecutives 0's
     *    variables[1] has 2 occurrences of 2 lines with consecutives 0's
     *    variables[2] has 4 coccurrences of 1 line with 'consecutive' 0
     *
     *    We can infer the rule for consecutives lines with 0 as:
     *        2^(n-1-variable_index).
     *    Using n-1 = 2:
     *        2^(2-0) = 2^2 = 4
     *        2^(2-1) = 2^1 = 2
     *        2^(2-2) = 2^0 = 1
     *
     *    And the number of occurrences per variable_index is:
     *        2^(variable_index)
     *    e.g.:
     *        2^0 = 1
     *        2^1 = 2
     *        2^2 = 4
     *    
     * To solve this problem we need to iterate trough every 0 and check it's
     * Hamming pair of Hamming distance 1. Since the 0's aren't all lined up
     * for most variables, we need a way to skip the 1's, for that we need a way
     * to dinamically determine a limit apart from a `consecutives` variable.
     *
     * Upon examination of the truth table we can find the following limits:
     *    variable 0: 4
     *    variable 1: 2, 6
     *    variable 2: 1, 3, 5, 7
     *
     * So the limit seems to start with the same value as the number of 
     * consecutives 0's and then turn into:
     *    limit = limit + 2^(consecutives)
     *
     * The start index of a new occurrence of consecutives 0's also has to be dinamic,
     * we can find it by going back `consecutives` number of times from the limit.
     *    start = limit - consecutives
     *
     * Since we know the position of the last consecutive 0 in each occurrence of a
     * cycle, we can infer that the position below it will be the Hamming pair for 
     * the new start
     */
    List *arcs = new_list();
    insert_at_end(arcs, "Transition Arcs:");

    // characteristics discussed at the top comment
    int consecutives;                // number of consecutives 0's/1's
    int hamming_pair;                // hamming distance of 1
    int occurrences;                 // number of cycles with 0's followed by 1's
    int n = tt->amount_of_variables; // n is also the result column
    
    // start and limit will change with each new occurrence of a cycle
    int start;                       // starting row
    int limit;                       // limit row

    // checks every possible arc for each variable
    for(int var_index = 0; var_index < n; var_index++) {
        consecutives = pow(2, (n-1) - var_index);
        occurrences = pow(2, var_index);

        start = 0;
        limit = consecutives;
        hamming_pair = limit;

        for(int i = 0; i < occurrences; i++) {
            for(int row = start; row < limit; row++) {
                if(tt->table[row][n] != tt->table[hamming_pair++][n])
                    insert_at_end(arcs, get_arc_string(tt, row, var_index));
            }
            limit += pow(2, consecutives);
            start = limit - consecutives;
            hamming_pair = limit;
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


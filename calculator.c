#include "calculator.h"
#include "utils.h"
#include <stdlib.h>


char *get_arc_string(Truth_table *tt, int row, int var_index) {
    int n = tt->n;
    char *arc_string = malloc(n);

    for(int i = 0; i < n; i++) {
        if(i == var_index)
            arc_string[i] = tt->variables[var_index];
        else
            arc_string[i] = bool_to_char(tt->table[row][i]);
    }

    return arc_string;
}

List *calculate_arcs(Truth_table *tt) {
    List *arcs = new_list();
    insert_at_end(arcs, "Transition Arcs:");
    int n = tt->n;

    int consecutives;
    int hamming_pair_index; // hamming distance of 1
    int repeat;
    for(int var_index = 0; var_index < n; var_index++) {
        hamming_pair_index = pow(2, (n-1) - var_index);
        consecutives = pow(2, (n-1) - var_index);
        repeat = pow(2, var_index);
        int start = 0;
        int lim = hamming_pair_index;
        for(int j = 0; j < repeat; j++) {
            for(int i = start; i < lim; i++) {
                if(tt->table[i][tt->n] != tt->table[hamming_pair_index++][tt->n])
                    insert_at_end(arcs, get_arc_string(tt, i, var_index));
            }
            lim += pow(2, consecutives);
            start = lim - consecutives;
            hamming_pair_index = lim;
        }
    }
  
    /* Arc jumps for n = 3
     * i = 0 --> +4 == 2^2 == 2^((n-1)-i)
     * i = 1 --> +2 == 2^1 == 2^((n-1)-i)
     * i = 3 --> +1 == 2^0 == 2^((n-1)-i)
     */
    return arcs;
}


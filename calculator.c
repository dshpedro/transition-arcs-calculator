#include "calculator.h"
#include "utils.h"
#include <stdlib.h>


char *get_arc_string(Truth_table *tt, int i) {
    char *arc_string = malloc(tt->n);
    arc_string[0] = 'a';
    for(int j = 1; j < tt->n; j++) {
        arc_string[j] = bool_to_char(tt->table[i][j]);
    }

    return arc_string;
}

List *calculate_arcs(Truth_table *tt) {
    List *arcs = new_list();
  
    int mid_row = tt->n / 2; // temporarily used for calculating only one arc
    int hamming_pair; // hamming distance of 1
    for(int i = 0; i < mid_row; i++) {
        hamming_pair = i + pow(2, (tt->n - 1) - i);    
        if(tt->table[i][tt->n] != tt->table[hamming_pair][tt->n])
            insert_at_end(arcs, get_arc_string(tt, i));
    }

    //for(int i = 0; i < tt->n; i++)

    /* Arc jumps for n = 3
     * i = 0 --> +4 == 2^2 == 2^((n-1)-i)
     * i = 1 --> +2 == 2^1 == 2^((n-1)-i)
     * i = 3 --> +1 == 2^0 == 2^((n-1)-i)
     */
    return arcs;
}


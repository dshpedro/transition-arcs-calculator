#include "truth_table.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    
    tt->table = malloc(tt->rows * sizeof(bool *));
    for(int i = 0; i < tt->rows; i++)
        tt->table[i] = malloc(n *sizeof(bool));

    populate_table(tt);
    return tt;
}

void populate_table(Truth_table *tt) {
    // dec == decimal
    for(int dec = 0; dec < tt->rows; dec++) {
        for(int i = 0; i < tt->n; i++) {
            tt->table[dec][(tt->n - 1) - i] = get_lsb(dec, i);
        }
    }
}

void print_truth_table(Truth_table *tt) {
    printf("%s\n", tt->variables);
    for(int i = 0; i < tt->rows; i++) {
        for(int j = 0; j < tt->n; j++) {
            if(tt->table[i][j])
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}


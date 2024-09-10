#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "truth_table.h"

void check_input(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    //check_input(argc, argv);
    Truth_table *tb = new_truth_table();
}

void check_input(int argc, char *argv[]) {
    for(int word = 1; word < argc; word++) {
        int c = 0;
        while(argv[word][c] != '\0') {
            if(isalpha(argv[word][c]) || 
               (argv[word][c] == ' '  && argv[word][c+1] == '+' && argv) ||
               argv[word][c] == '*' ||  
               argv[word][c] == '+')
                printf("char accepted\n");
            else { 
                printf("Invalid expression. Exiting program...\n");
                exit(EXIT_FAILURE);
            }
            c++;
        }
    }
}


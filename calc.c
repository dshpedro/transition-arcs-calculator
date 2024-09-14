#include "truth_table.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int get_number_of_variables(int argc, char *argv[]);
void check_input(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    int n = get_number_of_variables(argc, argv);
    n = 4;
    bool truth_table[(int) pow(2, n)][n]; // why didn't I think about this before??
    printf("Number of variables: %d\n", n);
    Truth_table *tb = new_truth_table(pow(2, n), n);
    print_truth_table(tb);
}

int get_number_of_variables(int argc, char *argv[]) {
    int letters[26] = {0};
    int i;
    for(int word = 1; word < argc; word++) {
        i = 0;
        while(argv[word][i] != '\0') {
            if(islower(argv[word][i])) {
                letters[(argv[word][i] - 'a')] += 1;
            }
            i++;
        }
    }
    
    int variables = 0;
    for(int i = 0; i < 26; i++) {
        // printf("%c: %d\n", 'a'+i, letters[i]); // debug
        if(letters[i] != 0)
            variables++;
    }
    return variables;
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
            exit(EXIT_FAILURE);
        }
    }
}


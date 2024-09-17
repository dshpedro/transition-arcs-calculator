#include "truth_table.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *get_variables(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    char *variables = get_variables(argc, argv);
    if(*variables == '\0') {
        printf("No variables were passed!\n");
        return EXIT_FAILURE;
    }
    Truth_table *tt = new_truth_table(variables);
    print_truth_table(tt);
}

char *get_variables(int argc, char *argv[]) {
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
    
    int n = 0;
    for(int i = 0; i < 26; i++) {
        //printf("%c: %d\n", 'a'+i, letters[i]); // debug
        if(letters[i] != 0)
            n++;
    }
  
    char *variables = malloc(n * sizeof(char));
    *variables = '\0';
    n = 0;
    for(int i = 0; i < 26; i++) {
        if(letters[i] != 0) {
            variables[n] = i + 'a';
            n++;
        }
    }

    return variables;
}


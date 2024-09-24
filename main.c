#include "truth_table.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_variables(char *expression);

int main(int argc, char *argv[]) {
    /* expressions will be passed between
     * single quotes and stored in argv[1]
     */
    char *expression = argv[1];
    char *variables = get_variables(expression);
    Truth_table *tt = new_truth_table(variables, expression);
    print_truth_table(tt);
}

char *get_variables(char *expression) {
    int letters[26] = {0};
    for(int i = 0; i < strlen(expression); i++) {
        if(islower(expression[i]))
            letters[(expression[i] - 'a')] += 1;
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


#include "utils.h"
#include <stdio.h>

bool is_input_valid(int argc, char *argv[]) {
    if(argv[1] != NULL)
        return true;
    else {
        printf("Invalid input!\n");
        return false;
    }
}

char *get_variables(char *expression) {
    int letters[26] = {0};
    for(int i = 0; i < strlen(expression); i++) {
        if(islower(expression[i]))
            letters[(expression[i] - 'a')] += 1;
    }
    
    int n = 0;
    for(int i = 0; i < 26; i++) {
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


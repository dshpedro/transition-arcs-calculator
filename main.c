#include "calculator.h"
#include "utils.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* expressions will be passed between
     * single quotes and stored in argv[1]
     */
    if(!is_input_valid(argc, argv))
        return 0;

    char *expression = argv[1];
    char *variables = get_variables(expression);
    Truth_table *tt = new_truth_table(variables, expression);
    List *arcs = calculate_arcs(tt);
    
    if(is_debug_mode(argc, argv)) {
        print_minterms(tt);
        print_truth_table(tt);
        printf("Transition Arcs:\n");
    }
    print_list(arcs);

    return 0;
}


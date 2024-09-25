#include "calculator.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    /* expressions will be passed between
     * single quotes and stored in argv[1]
     */
    if(!is_input_valid(argc, argv))
        return 0;

    char *expression = argv[1];
    char *variables = get_variables(expression);
    Truth_table *tt = new_truth_table(variables, expression);
    print_minterms(tt);
    print_truth_table(tt);

    List *arcs = calculate_arcs(tt);
    print_list(arcs);

    return 0;
}


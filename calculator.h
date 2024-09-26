#include "list.h"
#include "math.h"
#include "truth_table.h"

List *calculate_arcs(Truth_table *tt);
char *get_arc_string(Truth_table *tt, int row, int var_index);


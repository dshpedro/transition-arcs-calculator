#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char bool_to_char(bool value);
bool is_debug_mode(int argc, char *argv[]);
bool is_input_valid(int argc, char *argv[]);
char *get_variables(char *expression);


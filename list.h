#include <stdbool.h>

typedef struct List {
    bool value;
    struct List *next;
} List ;

List *new_list();


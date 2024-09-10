#include "list.h"
#include <stdlib.h>
#include <stdbool.h>

List *new_list() {
    List *list = malloc(sizeof *list);
    list->value = false;
    list->next = NULL;
    return list;
}


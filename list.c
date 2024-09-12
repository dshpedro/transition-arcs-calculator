#include "list.h"
#include <stdlib.h>
#include <stdio.h>

List *new_list() {
    List *list = malloc(sizeof *list);
    list->value = false;
    list->next = NULL;
    return list;
}

void print_list(List *list) {
    while(list != NULL) {
        if(list->value)
            printf("1");
        else
            printf("0");
        list = list->next;
    }
    printf("\n");
}


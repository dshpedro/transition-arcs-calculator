#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List *new_list() {
    List *list = malloc(sizeof *list);
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void print_list(List *list) {
    for(Node *curr = list->head; curr != NULL; curr = curr->next)
        printf("%s\n", curr->string);
}

void insert_at_end(List *list, char *string) {
    if(list == NULL || string == NULL)
        return;

    Node *new = malloc(sizeof *new);
    new->string = string;
    new->next = NULL;
    
    if(list->head == NULL)
        list->head = new;
    else
        list->tail->next = new;
    
    list->tail = new;
}


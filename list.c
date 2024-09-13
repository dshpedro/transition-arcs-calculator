#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List *new_list() {
    List *list = malloc(sizeof *list);
    list->head = NULL;
    return list;
}

void print_list(List *list) {
    Node *curr = list->head;
    while(curr != NULL) {
        if(curr->value)
            printf("1");
        else
            printf("0");
        curr = curr->next;
    }
    printf("\n");
}

void insert_at_start(List *list, bool value) {
    if(list != NULL) {
        Node *new = malloc(sizeof *new);
        new->value = value;
        new->next = list->head;
        list->head = new;
    }
}


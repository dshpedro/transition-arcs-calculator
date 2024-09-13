#include <stdbool.h>

typedef struct Node {
    bool value;
    struct Node *next;
} Node;

typedef struct List {
    struct Node *head;
} List;

void insert_at_start(List *list, bool value);
List *new_list();
void print_list(List *list);


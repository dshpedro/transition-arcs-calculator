typedef struct Node {
    char *string;
    struct Node *next;
} Node;

typedef struct List {
    struct Node *head;
    struct Node *tail;
} List;

void insert_at_end(List *list, char *string);
List *new_list();
void print_list(List *list);


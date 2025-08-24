#include "node.h"
#include <stdlib.h>
#include <stdio.h>

struct Node* create_node(int data)
{
    struct Node* node = malloc(sizeof(struct Node));
    if (!node) {
        printf("Memory allocation error\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void print_list(struct Node* head)
{
    struct Node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
    printf("NULL");
}

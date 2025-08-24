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
    printf("NULL\n");
}

void insert_at_beginning(struct Node** head_ref, int data)
{
    struct Node* node = create_node(data);
    node->next = *head_ref;
    *head_ref = node;
}

void insert_at_end(struct Node** head_ref, int data)
{
    struct Node* node = create_node(data);

    // checks for empty list
    if (*head_ref == NULL) {
        *head_ref = node;
        return;
    }    

    // navigate to last node, assign temp to the last node
    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

void free_list(struct Node* head)
{
    struct Node* current = head; 
    while (current != NULL) {
        struct Node* next_node = current->next;
        free(current);
        current = next_node;
    }
    head = NULL;
}

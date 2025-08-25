#include <stdio.h>
#include <stdlib.h>
#include "node.h"

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
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node* current = head;
    int counter = 0;
    while (current != NULL) {
        printf("%d: %d\n", counter, current->data);
        current = current->next;
        counter++;
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

    // navigate to last node, assign current to the last node
    struct Node* current = *head_ref;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

void insert_at_position(struct Node** head_ref, int data, int position)
{
    struct Node* node = create_node(data);
    struct Node** current = head_ref;

    // advance to the pointer that should point to the new node
    while (position > 0 && *current != NULL) {
        // set current to link of the next node
        current = &(*current)->next;
        position--;
    }
    node->next = *current;
    *current = node;
}

void free_list(struct Node** head_ref)
{
    struct Node* current = *head_ref; 
    struct Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head_ref = NULL;
}

int delete_at_position(struct Node** head_ref, int position)
{
    struct Node** current = head_ref;

    while (*current != NULL && position > 0) {
        current = &(*current)->next;
        position--;
    }

    if (*current == NULL) return -1;

    struct Node* delete_next_node = *current;
    *current = delete_next_node->next;
    free(delete_next_node);
    return 0;
}

struct Node* reverse_list(struct Node* head)
{
    struct Node* current = head, *previous = NULL, *next_node;

    // go through all nodes
    while (current != NULL) {
        // store next_node
        next_node = current->next;

        // reverse current node's next pointer
        current->next = previous;

        // move pointer on position ahead
        previous = current;
        current = next_node;
    }
    return previous;
}



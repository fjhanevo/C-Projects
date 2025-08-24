#include <stdio.h>

#include "node.h"

int main(void) {
    struct Node* head = NULL;

    insert_at_beginning(&head, 10);
    insert_at_beginning(&head, 20);
    insert_at_beginning(&head, 30);

    printf("Initial list: \n");
    print_list(head);

    /* insert_at_beginning(&head, 15); */
    /* insert_at_end(&head, 155); */
    // should be val 69 at position 2
    insert_at_position(&head, 69, 1); 

    printf("Modified list: \n");
    print_list(head);
        
    return 0;
}


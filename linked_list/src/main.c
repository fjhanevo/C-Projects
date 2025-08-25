#include <stdlib.h>

#include "node.h"

int main(void) {
    struct Node* head = NULL;

    print_list(head);
    insert_at_beginning(&head, 10);
    insert_at_beginning(&head, 20);
    insert_at_beginning(&head, 30);
    print_list(head);

    head = reverse_list(head);

    print_list(head);
    insert_at_position(&head, 66, 1);
    insert_at_position(&head, 99, 100); // should be placed at the end, as this position is invalid
    print_list(head);
    delete_at_position(&head, 1);
    delete_at_position(&head, 200); // should not delete anything as the position is invalid
    print_list(head);
    free_list(&head);
    print_list(head);

    return 0;
}


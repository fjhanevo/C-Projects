#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"

#define INPUT_SIZE 10

void menu(void);

int main(void)
{
    struct Contact phonebook[MAX_CONTACTS];
    int contact_count = 0;
    int option;
    char input[INPUT_SIZE];
    do {
        menu();
        // fgets to remove trailing newline from input
        fgets(input, sizeof(input), stdin);
        option = atoi(input);

        switch (option) {
            case 1:
                break;
            case 2:
                add_contact(phonebook, &contact_count);
                break;
            default:
                printf("Option: %d is not an alternative!\n", option);
        }
    } 
    while (option != 1);
    return 0;
}


void menu(void)
{
    printf("1. Exit\n");
    printf("2. Add contact\n");
}

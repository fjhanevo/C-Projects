#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "contacts.h"

#define INPUT_SIZE 50

void menu(void);

int main(void)
{
    struct Contact phonebook[MAX_CONTACTS];
    int contact_count = 0;
    int option;
    char input[INPUT_SIZE];
    bool flag = true;
    do {
        menu();
        // fgets to remove trailing newline from input
        fgets(input, sizeof(input), stdin);
        option = atoi(input);

        switch (option) {
            case 1:
                flag = false;
                break;
            case 2:
                add_contact(phonebook, &contact_count);
                break;
            case 3:
                list_contacts(phonebook, &contact_count);
                break;
            case 4: 
                search_contacts(phonebook, &contact_count);
                break;
            default:
                printf("Option: %d is not an alternative!\n", option);
        }
    } 
    while (flag);
    printf("Contact count: %d\n", contact_count);
    return 0;
}


void menu(void)
{
    printf("1. Exit\n");
    printf("2. Add contact\n");
    printf("3. List contacts\n");
    printf("4. Search contacts\n");
}

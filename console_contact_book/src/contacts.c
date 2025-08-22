#include "contacts.h"
#include <stdio.h>
#include <string.h>

void add_contact(struct Contact phonebook[], int *contact_count)
{
    int index = *contact_count;  

    if (index >= MAX_CONTACTS) {
        printf("Phonebook is full!");
        return;
    }

    char name_buffer[NAME_SIZE];
    char phone_buffer[PHONE_SIZE];
    char email_buffer[EMAIL_SIZE];

    printf("Type in the name of the contact: ");
    fgets(name_buffer, sizeof(name_buffer), stdin);
    // Removes trailing newline from input
    name_buffer[strcspn(name_buffer, "\n")] = 0;

    printf("Type in the phone number of the contact: ");
    fgets(phone_buffer, sizeof(phone_buffer), stdin);
    phone_buffer[strcspn(phone_buffer, "\n")] = 0;

    printf("Type in the email of the contact: ");
    fgets(email_buffer, sizeof(email_buffer), stdin);
    email_buffer[strcspn(email_buffer, "\n")] = 0;

    strcpy(phonebook[index].name, name_buffer);
    strcpy(phonebook[index].phone, phone_buffer);
    strcpy(phonebook[index].email, email_buffer);

    (*contact_count)++;

    printf("Contact added successfully!\n");
}

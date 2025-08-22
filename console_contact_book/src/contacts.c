#include "contacts.h"
#include <stdio.h>
#include <string.h>


static void print_contacts(struct Contact phonebook[], unsigned int index)
{
        printf("Name: %s\n",phonebook[index].name);
        printf("Phone: %s\n",phonebook[index].phone);
        printf("Email: %s\n\n",phonebook[index].email);
}

void add_contact(struct Contact phonebook[], int *contact_count)
{
    int index = *contact_count;  

    if (index >= MAX_CONTACTS) {
        printf("Phonebook is full!\n");
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

void list_contacts(struct Contact phonebook[], int *contact_count)
{
    if (*contact_count == 0) {
        printf("Contact list is empty!\n");
        return;
    }

    for (unsigned int i = 0; i < *contact_count; i++) {
        print_contacts(phonebook, i);
    }
}

void search_contacts(struct Contact phonebook[], int *contact_count)
{
    if (*contact_count == 0) {
        printf("No contacts to search for!\n");
        return;
    }  

    printf("Please type in a name to search for: ");
    char search[NAME_SIZE];
    fgets(search, sizeof(search), stdin);
    // Remove trailing newline
    search[strcspn(search, "\n")] = 0;

    // Search through contact list for the name
    for (unsigned int i = 0; i < *contact_count; i++) {
        if (strcmp(search, phonebook[i].name) == 0) {
            printf("Contact found!\n");
            print_contacts(phonebook, i);
            return;
        }
    }
    printf("Contact not found!\n");
}

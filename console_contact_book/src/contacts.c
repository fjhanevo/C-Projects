#include "contacts.h"
#include <stdio.h>
#include <string.h>

static void print_contact(struct Contact phonebook[], unsigned int index)
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
        print_contact(phonebook, i);
    }
}

void search_contact(struct Contact phonebook[], int *contact_count)
{
    if (*contact_count == 0) {
        printf("No contacts to search for!\n");
        return;
    }  

    printf("Please type in a name to search for: ");
    char contact_name[NAME_SIZE];
    fgets(contact_name, sizeof(contact_name), stdin);
    // Remove trailing newline
    contact_name[strcspn(contact_name, "\n")] = 0;

    // contact_name through contact list for the name
    for (unsigned int i = 0; i < *contact_count; i++) {
        if (strcmp(contact_name, phonebook[i].name) == 0) {
            printf("Contact found!\n");
            print_contact(phonebook, i);
            return;
        }
    }
    printf("Contact not found!\n");
}

void delete_contact(struct Contact phonebook[], int *contact_count)
{
 
    if (*contact_count == 0) {
        printf("No contacts to delete!\n");
        return;
    }

    printf("Type name of contact to delete: ");
    char contact_name[NAME_SIZE];
    fgets(contact_name, sizeof(contact_name), stdin);
    contact_name[strcspn(contact_name, "\n")] = 0;

    for (unsigned int i = 0; i < *contact_count; i++) {
        if (strcmp(contact_name, phonebook[i].name) == 0) {
            printf("Deleting contact: %s\n", phonebook[i].name);
            // Delete element and shift all other elements
            for (unsigned int j = i; j < (*contact_count - 1); j++) {
                phonebook[j] = phonebook[j+1];
            }
            (*contact_count)--;
            return;
        }
    }
    printf("Contact not found!\n");
}

void save_contacts(struct Contact phonebook[], int *contact_count)
{
    FILE* file = fopen("contact_log.txt", "w");
    if (file == NULL) {
        printf("Error: Could not save contacts to file!\n");
        return;
    }

    for (unsigned int i = 0; i < *contact_count; i++) {
        fprintf(file, "%s, %s, %s\n", phonebook[i].name, phonebook[i].phone, phonebook[i].email);
    }

    fclose(file);
}

int load_contacts(struct Contact phonebook[], int *contact_count)
{
    FILE* file = fopen("contact_log.txt", "r");

    if (file == NULL) {
        printf("No contact log found. Creating new one upon saving.\n");
        *contact_count = 0;
        return 0;
    }

    char buf[BUFF_SIZE];
    *contact_count = 0;

    // read file line by line
    while (fgets(buf, sizeof(buf), file) != NULL && *contact_count < MAX_CONTACTS) {
        // parse csv from the buffer
        // format string to prevent buffer overflow
        sscanf(buf, "%49[^,], %49[^,], %49[^\n]",
               phonebook[*contact_count].name, 
               phonebook[*contact_count].phone,
               phonebook[*contact_count].email);
        (*contact_count)++;
    }

    fclose(file);
    printf("%d contact(s) loaded.\n", *contact_count);

    return *contact_count;

}



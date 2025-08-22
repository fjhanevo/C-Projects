#define MAX_CONTACTS 100
#define NAME_SIZE 50
#define PHONE_SIZE 9
#define EMAIL_SIZE 50

struct Contact {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    char email[EMAIL_SIZE];
};

void add_contact(struct Contact phonebook[], int *contact_count);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 100 // Define the size of the hash table
typedef struct Contact {
    char name[50];
    char phoneNumber[20];
    struct Contact *next;
} Contact;
Contact *hashTable[TABLE_SIZE];
unsigned int hashFunction(const char *name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash << 5) + *name++;
    }
    return hash % TABLE_SIZE;
}
void addContact(const char *name, const char *phoneNumber) {
    unsigned int index = hashFunction(name);
    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phoneNumber, phoneNumber);
    newContact->next = NULL;
   if (hashTable[index] == NULL) {
        hashTable[index] = newContact;
    } else {
        Contact *temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }
printf("Contact added successfully!\n");
}
void searchContact(const char *name) {
    unsigned int index = hashFunction(name);
    Contact *temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Contact Found:\nName: %s\nPhone Number: %s\n", temp->name, temp->phoneNumber);
            return;
        }
        temp = temp->next;
    }
    printf("Contact not found.\n");
}
void displayContacts() {
    printf("Phonebook Contacts:\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Contact *temp = hashTable[i];
        while (temp != NULL) {
            printf("Name: %s, Phone Number: %s\n", temp->name, temp->phoneNumber);
            temp = temp->next;
        }
    }
}

// Main function
int main() {
    // Initialize hash table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable[i] = NULL;
    }

    int choice;
    char name[50];
    char phoneNumber[20];

    do {
        printf("\nPhonebook Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display Contacts\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter contact name: ");
                scanf("%s", name);
                printf("Enter phone number: ");
                scanf("%s", phoneNumber);
                addContact(name, phoneNumber);
                break;
            case 2:
                printf("Enter contact name to search: ");
                scanf("%s", name);
                searchContact(name);
                break;
            case 3:
                displayContacts();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}

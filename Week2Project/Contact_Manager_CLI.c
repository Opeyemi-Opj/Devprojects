#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_PHONE 20
#define MAX_EMAIL 100

struct Contact {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
};

struct Contact *contacts = NULL;
int contactCount = 0;
int contactCapacity = 0;

// Increase memory for contact array
void ensureCapacity() {
    if (contactCount >= contactCapacity) {
        contactCapacity = contactCapacity == 0 ? 10 : contactCapacity * 2;
        contacts = realloc(contacts, contactCapacity * sizeof(struct Contact));
        if (!contacts) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
}

// Load contacts from file
void loadContacts() {
    FILE *file = fopen("contacts.csv", "r");
    if (!file) {
        printf("No existing contacts. Starting fresh.\n");
        return;
    }

    struct Contact temp;
    while (fscanf(file, "%99[^,],%19[^,],%99[^\n]\n",
                  temp.name, temp.phone, temp.email) == 3) {
        ensureCapacity();
        contacts[contactCount++] = temp;
    }

    fclose(file);
}

// Save contacts to file
void saveContacts() {
    FILE *file = fopen("contacts.csv", "w");
    if (!file) {
        printf("Failed to save contacts.\n");
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                contacts[i].name,
                contacts[i].phone,
                contacts[i].email);
    }

    fclose(file);
}

// Add contact
void addContact(char *name, char *phone, char *email) {
    ensureCapacity();
    strncpy(contacts[contactCount].name, name, MAX_NAME);
    strncpy(contacts[contactCount].phone, phone, MAX_PHONE);
    strncpy(contacts[contactCount].email, email, MAX_EMAIL);
    contactCount++;

    printf("Contact added: %s\n", name);
    saveContacts();
}

// Search
void searchContact(char *query) {
    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        if (strstr(contacts[i].name, query) != NULL) {
            printf("Found: %s | %s | %s\n",
                   contacts[i].name,
                   contacts[i].phone,
                   contacts[i].email);
            found = 1;
        }
    }
    if (!found)
        printf("No contact found matching: %s\n", query);
}

// Remove
void removeContact(char *name) {
    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            for (int j = i; j < contactCount - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            contactCount--;
            found = 1;
            printf("Contact removed: %s\n", name);
            saveContacts();
            break;
        }
    }
    if (!found)
        printf("Contact not found: %s\n", name);
}

// Show stats
void showStats() {
    printf("Total contacts loaded: %d\n", contactCount);
    printf("Size of each contact: %lu bytes\n", sizeof(struct Contact));
    printf("Total memory used: %lu bytes\n", contactCount * sizeof(struct Contact));
}

int main(int argc, char *argv[]) {
    loadContacts();

    if (argc < 2) {
        printf("Usage:\n");
        printf("  add \"Name\" \"Phone\" \"Email\"\n");
        printf("  search \"Name\"\n");
        printf("  remove \"Name\"\n");
        printf("  stats\n");
        free(contacts);
        return 1;
    }

    if (strcmp(argv[1], "add") == 0 && argc == 5) {
        addContact(argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[1], "search") == 0 && argc == 3) {
        searchContact(argv[2]);
    } else if (strcmp(argv[1], "remove") == 0 && argc == 3) {
        removeContact(argv[2]);
    } else if (strcmp(argv[1], "stats") == 0) {
        showStats();
    } else {
        printf("Invalid command or arguments.\n");
    }

    // Memory cleanup
    free(contacts);
    return 0;
}

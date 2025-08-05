#include <stdio.h>     // For input/output operations
#include <stdlib.h>    // For dynamic memory functions: malloc, realloc, free
#include <string.h>    // For string manipulation functions

#define MAX_LINE 256   // Max length for a line read from the CSV file

// Define a structure for a contact
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Function to display all contacts
void display_contacts(Contact *contacts, int count) {
    printf("\n--- All Contacts ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Name: %s | Phone: %s | Email: %s\n",
               i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

// Function to save all contacts to a CSV file
void save_contacts(const char *filename, Contact *contacts, int count) {
    FILE *file = fopen(filename, "w");  // Open file for writing
    if (file == NULL) {
        printf("Error saving file.\n");
        return;
    }

    // Write CSV header
    fprintf(file, "Name,Phone,Email\n");

    // Write each contact to the file
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(file); // Close the file
    printf("Contacts saved to %s\n", filename);
}

// Function to load contacts from a CSV file
int load_contacts(const char *filename, Contact **contacts) {
    FILE *file = fopen(filename, "r");  // Open file for reading
    if (file == NULL) {
        printf("File not found. Starting with empty contact list.\n");
        return 0;
    }

    char line[MAX_LINE];
    int count = 0;

    fgets(line, MAX_LINE, file);  // Skip the header line

    // Read contact details line by line
    while (fgets(line, MAX_LINE, file)) {
        *contacts = realloc(*contacts, (count + 1) * sizeof(Contact)); // Increase memory
        sscanf(line, "%49[^,],%19[^,],%49[^\n]",                    // Parse the line into struct fields
               (*contacts)[count].name,
               (*contacts)[count].phone,
               (*contacts)[count].email);
        count++;
    }

    fclose(file);
    return count;  // Return number of contacts loaded
}

// Function to add a new contact
void add_contact(Contact **contacts, int *count) {
    Contact new;

    // Get new contact details from user
    printf("Enter name: ");
    scanf(" %[^\n]", new.name);
    printf("Enter phone: ");
    scanf(" %[^\n]", new.phone);
    printf("Enter email: ");
    scanf(" %[^\n]", new.email);

    // Resize memory and add new contact
    *contacts = realloc(*contacts, (*count + 1) * sizeof(Contact));
    (*contacts)[*count] = new;
    (*count)++;

    printf("Contact added successfully!\n");
}

// Function to update an existing contact
void update_contact(Contact *contacts, int count) {
    display_contacts(contacts, count);  // Show all contacts first

    int index;
    printf("Enter contact number to update: ");
    scanf("%d", &index);

    // Validate index
    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }

    index--; // Adjust to 0-based index

    // Get new values for the selected contact
    printf("Enter new name: ");
    scanf(" %[^\n]", contacts[index].name);
    printf("Enter new phone: ");
    scanf(" %[^\n]", contacts[index].phone);
    printf("Enter new email: ");
    scanf(" %[^\n]", contacts[index].email);

    printf("Contact updated.\n");
}

// Function to delete a contact
void delete_contact(Contact **contacts, int *count) {
    display_contacts(*contacts, *count);  // Show all contacts

    int index;
    printf("Enter contact number to delete: ");
    scanf("%d", &index);

    // Validate index
    if (index < 1 || index > *count) {
        printf("Invalid contact number.\n");
        return;
    }

    index--; // Adjust to 0-based index

    // Shift remaining contacts one position up
    for (int i = index; i < *count - 1; i++) {
        (*contacts)[i] = (*contacts)[i + 1];
    }

    (*count)--; // Decrease total count
    *contacts = realloc(*contacts, (*count) * sizeof(Contact)); // Resize memory
    printf("Contact deleted.\n");
}

// Main function
int main() {
    const char *filename = "Project_contact.csv";  // File to store contact info
    Contact *contacts = NULL;                       // Pointer to contacts array
    int count = load_contacts(filename, &contacts); // Load existing contacts

    int choice;
    do {
        // Menu display
        printf("\n==== Contacts Manager ====\n");
        printf("1. Display contacts\n");
        printf("2. Add contact\n");
        printf("3. Update contact\n");
        printf("4. Delete contact\n");
        printf("5. Exit and Save\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        // Handle user's choice
        switch (choice) {
            case 1: display_contacts(contacts, count); break;
            case 2: add_contact(&contacts, &count); break;
            case 3: update_contact(contacts, count); break;
            case 4: delete_contact(&contacts, &count); break;
            case 5: save_contacts(filename, contacts, count); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);  // Repeat until user chooses to exit

    free(contacts);  // Free allocated memory
    return 0;
}

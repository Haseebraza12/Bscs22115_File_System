#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {
    printf("\n--- File System Menu ---\n");
    printf("1. Create File\n");
    printf("2. Read File\n");
    printf("3. Write File\n");
    printf("4. Delete File\n");
    printf("5. List Files\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    initialize_file_system();

    int choice;
    char name[MAX_FILE_NAME_SIZE];
    char content[MAX_FILE_SIZE];

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1: // Create File
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                printf("Enter file content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0'; // Remove newline
                create_file(name, content);
                break;

            case 2: // Read File
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                read_file(name);
                break;

            case 3: // Write File
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter new content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                write_file(name, content);
                break;

            case 4: // Delete File
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                delete_file(name);
                break;

            case 5: // List Files
                list_files();
                break;

            case 6: // Exit
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

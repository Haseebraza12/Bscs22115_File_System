#include "filesystem.h"
#include <stdio.h>

void menu() {
    printf("\n--- File System Menu ---\n");
    printf("1. Create File\n");
    printf("2. Read File\n");
    printf("3. Write File\n");
    printf("4. Truncate File\n");
    printf("5. Delete File\n");
    printf("6. List Files\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    create_file_system();  // Ensures the file system is ready
    int choice;
    char name[MAX_FILE_NAME_SIZE];
    char content[MAX_FILE_SIZE];

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                fgets(name, MAX_FILE_NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline
                printf("Enter file content: ");
                fgets(content, MAX_FILE_SIZE, stdin);
                content[strcspn(content, "\n")] = '\0'; // Remove newline
                create_file(name, content);
                break;
            case 2:
                printf("Enter file name: ");
                fgets(name, MAX_FILE_NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                read_file(name);
                break;
            case 3:
                printf("Enter file name: ");
                fgets(name, MAX_FILE_NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter new content: ");
                fgets(content, MAX_FILE_SIZE, stdin);
                content[strcspn(content, "\n")] = '\0';
                write_file(name, content);
                break;
            case 4:
                printf("Enter file name: ");
                fgets(name, MAX_FILE_NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                truncate_file(name);
                break;
            case 5:
                printf("Enter file name: ");
                fgets(name, MAX_FILE_NAME_SIZE, stdin);
                name[strcspn(name, "\n")] = '\0';
                delete_file(name);
                break;
            case 6:
                list_files();
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {
    printf("\n--- File System Menu ---\n");
    printf("1. Create File\n");
    printf("2. Read File\n");
    printf("3. Write to File\n");
    printf("4. Delete File\n");
    printf("5. Truncate File\n");
    printf("6. List Files\n");
    printf("7. Create Directory\n");
    printf("8. Delete Directory\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    initialize_file_system();

    int choice;
    char name[MAX_FILE_NAME_SIZE];
    char content[BLOCK_SIZE];
    int new_size;

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter file content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                create_file(name, content);
                break;

            case 2:
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                read_file(name);
                break;

            case 3:
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter content to append: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                write_file(name, content);
                break;

            case 4:
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                delete_file(name);
                break;

            case 5:
                printf("Enter file name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter new size (in bytes): ");
                scanf("%d", &new_size);
                getchar();
                truncate_file(name, new_size);
                break;

            case 6:
                list_files();
                break;

            case 7:
                printf("Enter directory name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                create_directory(name);
                break;

            case 8:
                printf("Enter directory name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                delete_directory(name);
                break;

            case 9:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}

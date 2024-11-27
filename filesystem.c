#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void initialize_file_system() {
    struct stat st = {0};

    // Check if the directory exists, if not create it
    if (stat(FILE_SYSTEM_DIR, &st) == -1) {
        if (mkdir(FILE_SYSTEM_DIR, 0700) == 0) {
            printf("Initialized virtual file system in directory '%s'.\n", FILE_SYSTEM_DIR);
        } else {
            perror("Error initializing file system");
            exit(1);
        }
    }
}

void create_file(const char* name, const char* content) {
    char path[MAX_FILE_NAME_SIZE + sizeof(FILE_SYSTEM_DIR) + 2];
    snprintf(path, sizeof(path), "%s/%s", FILE_SYSTEM_DIR, name);

    FILE* file = fopen(path, "w");
    if (!file) {
        perror("Error creating file");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);
    printf("File '%s' created successfully.\n", name);
}

void read_file(const char* name) {
    char path[MAX_FILE_NAME_SIZE + sizeof(FILE_SYSTEM_DIR) + 2];
    snprintf(path, sizeof(path), "%s/%s", FILE_SYSTEM_DIR, name);

    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error: File '%s' not found.\n", name);
        return;
    }

    char buffer[MAX_FILE_SIZE];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[bytes_read] = '\0';

    printf("Content of '%s':\n%s\n", name, buffer);
    fclose(file);
}

void write_file(const char* name, const char* content) {
    char path[MAX_FILE_NAME_SIZE + sizeof(FILE_SYSTEM_DIR) + 2];
    snprintf(path, sizeof(path), "%s/%s", FILE_SYSTEM_DIR, name);

    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Error: File '%s' not found.\n", name);
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);
    printf("File '%s' updated successfully.\n", name);
}

void delete_file(const char* name) {
    char path[MAX_FILE_NAME_SIZE + sizeof(FILE_SYSTEM_DIR) + 2];
    snprintf(path, sizeof(path), "%s/%s", FILE_SYSTEM_DIR, name);

    if (remove(path) == 0) {
        printf("File '%s' deleted successfully.\n", name);
    } else {
        printf("Error: File '%s' not found.\n", name);
    }
}

void list_files() {
    DIR* dir = opendir(FILE_SYSTEM_DIR);
    if (!dir) {
        perror("Error opening file system directory");
        return;
    }

    printf("\n--- Files in '%s' ---\n", FILE_SYSTEM_DIR);
    struct dirent* entry;
    char path[MAX_FILE_NAME_SIZE + sizeof(FILE_SYSTEM_DIR) + 2];
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", FILE_SYSTEM_DIR, entry->d_name);

        // Use stat to check if it's a regular file
        if (stat(path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}


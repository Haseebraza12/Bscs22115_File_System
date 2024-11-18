#include "filesystem.h"

// Global variables
FILE *fs;
DirectoryEntry directory[DIRECTORY_SIZE];
int current_directory_size = 0;

void create_file_system() {
    fs = fopen(FILE_SYSTEM_NAME, "rb+");
    if (fs == NULL) {
        fs = fopen(FILE_SYSTEM_NAME, "wb+");
        if (fs == NULL) {
            printf("Failed to create file system.\n");
            exit(1);
        }
        // Initialize the file system (directory block)
        fseek(fs, 0, SEEK_SET);
        fwrite(directory, sizeof(DirectoryEntry), DIRECTORY_SIZE, fs);
    }
}

int allocate_blocks(int size) {
    int blocks_needed = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    // Allocate blocks by finding empty blocks
    return blocks_needed;
}

void free_blocks(int start_block) {
    // Free blocks (this can be expanded to actually mark blocks as free)
}

void create_file(const char *name, const char *content) {
    if (current_directory_size >= DIRECTORY_SIZE) {
        printf("Directory is full.\n");
        return;
    }

    DirectoryEntry entry;
    strncpy(entry.name, name, MAX_FILE_NAME_SIZE);
    entry.size = strlen(content);
    entry.start_block = allocate_blocks(entry.size);
    entry.is_directory = 0;

    directory[current_directory_size++] = entry;

    // Write content to the file system (after the directory block)
    fseek(fs, entry.start_block * BLOCK_SIZE, SEEK_SET);
    fwrite(content, sizeof(char), entry.size, fs);

    // Update the directory in the file system
    fseek(fs, 0, SEEK_SET);
    fwrite(directory, sizeof(DirectoryEntry), DIRECTORY_SIZE, fs);

    printf("File created successfully: %s\n", name);
}

void read_file(const char *name) {
    for (int i = 0; i < current_directory_size; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            char *content = (char *)malloc(directory[i].size);
            fseek(fs, directory[i].start_block * BLOCK_SIZE, SEEK_SET);
            fread(content, sizeof(char), directory[i].size, fs);
            printf("File content: %s\n", content);
            free(content);
            return;
        }
    }
    printf("File not found.\n");
}

void write_file(const char *name, const char *content) {
    for (int i = 0; i < current_directory_size; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            directory[i].size = strlen(content);
            fseek(fs, directory[i].start_block * BLOCK_SIZE, SEEK_SET);
            fwrite(content, sizeof(char), directory[i].size, fs);
            printf("File written successfully: %s\n", name);
            return;
        }
    }
    printf("File not found.\n");
}

void truncate_file(const char *name) {
    for (int i = 0; i < current_directory_size; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            directory[i].size = 0;
            fseek(fs, directory[i].start_block * BLOCK_SIZE, SEEK_SET);
            fwrite("", sizeof(char), 0, fs);
            printf("File truncated: %s\n", name);
            return;
        }
    }
    printf("File not found.\n");
}

void delete_file(const char *name) {
    for (int i = 0; i < current_directory_size; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            // Free blocks and remove from directory
            free_blocks(directory[i].start_block);
            for (int j = i; j < current_directory_size - 1; j++) {
                directory[j] = directory[j + 1];
            }
            current_directory_size--;
            // Update the directory in the file system
            fseek(fs, 0, SEEK_SET);
            fwrite(directory, sizeof(DirectoryEntry), DIRECTORY_SIZE, fs);
            printf("File deleted: %s\n", name);
            return;
        }
    }
    printf("File not found.\n");
}

void list_files() {
    if (current_directory_size == 0) {
        printf("No files in the directory.\n");
        return;
    }
    for (int i = 0; i < current_directory_size; i++) {
        printf("File: %s, Size: %d bytes\n", directory[i].name, directory[i].size);
    }
}

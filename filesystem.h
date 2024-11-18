#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIRECTORY_SIZE 128
#define MAX_FILE_NAME_SIZE 64
#define MAX_FILE_SIZE 128
#define BLOCK_SIZE 1024
#define TOTAL_DISK_SIZE (1 * 1024 * 1024 * 1024) // 1GB disk
#define TOTAL_BLOCKS (TOTAL_DISK_SIZE / BLOCK_SIZE)
#define FILE_SYSTEM_NAME "Haseeb.FAT" // Define the file system name

// Struct to represent a file or directory entry in the file system
typedef struct {
    char name[MAX_FILE_NAME_SIZE];
    int start_block;  // Starting block in FAT
    int size;         // File size in bytes
    int is_directory; // 1 for directory, 0 for file
} DirectoryEntry;

// Function declarations
void create_file_system();
void create_file(const char *name, const char *content);
void read_file(const char *name);
void write_file(const char *name, const char *content);
void truncate_file(const char *name);
void delete_file(const char *name);
void list_files();
int allocate_blocks(int size);
void free_blocks(int start_block);

#endif

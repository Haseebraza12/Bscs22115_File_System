#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdbool.h>

#define MAX_FILE_NAME_SIZE 64 // Maximum file name size (bytes)
#define MAX_FILE_SIZE 128     // Maximum file size (blocks)
#define BLOCK_SIZE 1024       // Block size (bytes)
#define DISK_SIZE (64 * 1024 * 1024) // Total disk size (64 MB)
#define TOTAL_BLOCKS (DISK_SIZE / BLOCK_SIZE) // Total number of blocks
#define MAX_ENTRIES 128       // Directory size (entries)
#define FILE_SYSTEM_DIR "virtual_fs" // Directory for virtual file system

typedef struct {
    char name[MAX_FILE_NAME_SIZE]; // File name
    int size;                      // File size (in bytes)
    int blocks[MAX_FILE_SIZE];     // Array of block indices
    bool used;                     // File existence flag
} FileEntry;

typedef struct {
    FileEntry entries[MAX_ENTRIES]; // Directory entries
    int free_blocks[TOTAL_BLOCKS];  // Free block table
} FileSystem;

// Global file system structure
extern FileSystem fs;

// Function declarations
void initialize_file_system();
void create_file(const char* name, const char* content);
void read_file(const char* name);
void write_file(const char* name, const char* content);
void delete_file(const char* name);
void truncate_file(const char* name, int new_size);
void list_files();
void create_directory(const char* name);
void delete_directory(const char* name);

#endif // FILESYSTEM_H

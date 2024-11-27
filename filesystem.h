#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define MAX_FILE_NAME_SIZE 32
#define MAX_FILE_SIZE 1024
#define FILE_SYSTEM_DIR "virtual_fs" // Directory for storing files

// Function declarations
void initialize_file_system();
void create_file(const char* name, const char* content);
void read_file(const char* name);
void write_file(const char* name, const char* content);
void delete_file(const char* name);
void list_files();

#endif // FILESYSTEM_H

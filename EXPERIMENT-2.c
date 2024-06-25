#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    char *source_file = argv[1];
    char *destination_file = argv[2];

    // Open the source file for reading
    int fd_source = open(source_file, O_RDONLY);
    if (fd_source == -1) {
        perror("Failed to open source file");
        return 1;
    }

    // Open the destination file for writing (create if it doesn't exist, truncate if it does)
    int fd_dest = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1) {
        perror("Failed to open destination file");
        close(fd_source);
        return 1;
    }

    // Buffer for read/write operations
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Read from source and write to destination
    while ((bytes_read = read(fd_source, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Write error");
            close(fd_source);
            close(fd_dest);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Read error");
        close(fd_source);
        close(fd_dest);
        return 1;
    }

    // Close files
    close(fd_source);
    close(fd_dest);

    printf("File copied successfully.\n");

    return 0;
}


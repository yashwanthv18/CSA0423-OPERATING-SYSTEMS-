#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;
    struct passwd *pw;
    struct group *gr;
    char file_permissions[11]; // Store file permissions in string format
    char last_modified[20]; // Store last modified time in string format

    dir = opendir(path);
    if (dir == NULL)
        handle_error("Error opening directory");

    printf("Listing directory: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        // Get file information
        if (stat(entry->d_name, &file_info) == -1)
            handle_error("Error getting file information");

        // Convert file permissions to string format
        snprintf(file_permissions, sizeof(file_permissions), 
                 "%s%s%s%s%s%s%s%s%s%s",
                 (S_ISDIR(file_info.st_mode)) ? "d" : "-",
                 (file_info.st_mode & S_IRUSR) ? "r" : "-",
                 (file_info.st_mode & S_IWUSR) ? "w" : "-",
                 (file_info.st_mode & S_IXUSR) ? "x" : "-",
                 (file_info.st_mode & S_IRGRP) ? "r" : "-",
                 (file_info.st_mode & S_IWGRP) ? "w" : "-",
                 (file_info.st_mode & S_IXGRP) ? "x" : "-",
                 (file_info.st_mode & S_IROTH) ? "r" : "-",
                 (file_info.st_mode & S_IWOTH) ? "w" : "-",
                 (file_info.st_mode & S_IXOTH) ? "x" : "-");

        // Get last modified time in string format
        strftime(last_modified, sizeof(last_modified), "%b %d %Y %H:%M", localtime(&file_info.st_mtime));

        // Get owner and group names
        pw = getpwuid(file_info.st_uid);
        gr = getgrgid(file_info.st_gid);

        // Print formatted output
        printf("%s  %2ld  %-8s %-8s  %8ld  %s  %s\n", 
               file_permissions, file_info.st_nlink, 
               pw->pw_name, gr->gr_name, 
               file_info.st_size, last_modified, 
               entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path;

    if (argc == 1) {
        // No directory specified, list current directory
        path = ".";
    } else if (argc == 2) {
        // Directory specified as command-line argument
        path = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }

    list_directory(path);

    return 0;
}

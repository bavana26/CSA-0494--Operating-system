#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("Unable to open directory: %s\n", argv[1]);
        return 1;
    }

    // Read and print the contents of the directory
    printf("Contents of directory '%s':\n", argv[1]);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

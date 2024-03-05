#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char* select_file_from_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    char *files[256];
    int count = 0;
    static char selected_file_path[1024];

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    printf("Files in %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            if (count >= 256) {
                fprintf(stderr, "Too many files in the directory\n");
                break;
            }
            files[count] = strdup(entry->d_name);
            printf("%d: %s\n", count + 1, files[count]);
            count++;
        }
    }

    printf("Enter the number of the file you want to select: ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input\n");
        return NULL;
    }

    if (choice < 1 || choice > count) {
        fprintf(stderr, "Invalid selection.\n");
        return NULL;
    }

    int path_len = strlen(path);
    if (path[path_len - 1] == '/') {
        snprintf(selected_file_path, sizeof(selected_file_path), "%s%s", path, files[choice - 1]);
    } else {
        snprintf(selected_file_path, sizeof(selected_file_path), "%s/%s", path, files[choice - 1]);
    }

    for (int i = 0; i < count; i++) {
        free(files[i]);
    }
    closedir(dir);

    return selected_file_path;
}

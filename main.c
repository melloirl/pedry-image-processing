#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./utils/fs.h"
#include "./operations/operations.h"
#include "./operations/distance.h"

char* extract_filename(const char *path) {
    const char *last_slash = strrchr(path, '/');
    if (last_slash == NULL) {
        // Make a copy of the path and return it
        char *copy = malloc(strlen(path) + 1); // +1 for null terminator
        if (copy == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
        strcpy(copy, path);
        return copy;
    } else {
        // Make a copy of the substring and return it
        last_slash++; // Move past the slash
        char *copy = malloc(strlen(last_slash) + 1); // +1 for null terminator
        if (copy == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
        strcpy(copy, last_slash);
        return copy;
    }
}

char* concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main() {
    printf("What operation would you like to perform?\n");
    printf("1. Copy\n");
    printf("2. Blur\n");
    int operation;
    if (scanf("%d", &operation) != 1) {
        fprintf(stderr, "Failed to read the operation.\n");
        return 1;
    }

    // Prompts the user to select an image from the images folder
    printf("Select an image from the images folder\n");
    char* path = select_file_from_directory("./images");

    if (path == NULL) {
        fprintf(stderr, "No file selected.\n");
        return 1;
    }

    char* outpath;
    if (operation == 1) {
        char* filename = extract_filename(path);
        outpath = concat("./out/copy_", filename);
        copy(path, outpath);
    } else if (operation == 2) {
        char* filename = extract_filename(path);
        outpath = concat("./out/blur_", filename);
        blur_grey(path, outpath);
    } else {
        fprintf(stderr, "Invalid operation selected.\n");
        free(path);
        return 1;
    }

    return 0;
}

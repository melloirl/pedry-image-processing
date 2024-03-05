#ifndef FS_H
#define FS_H

/**
 * Allows a user to select a file from the given directory.
 * @param path The path to the directory.
 * @return The path to the selected file. This is a static buffer and should not be modified.
 */
char* select_file_from_directory(const char *path);

#endif // FS_H

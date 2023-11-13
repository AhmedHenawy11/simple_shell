#include "main.h"
#include <sys/stat.h>

char *command_path(char *command)
{
    char *path, *path_copy, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    // Get the PATH environment variable
    path = getenv("PATH");

    if (path) {
        // Duplicate the path string
        path_copy = strdup(path);

        if (!path_copy) {
            perror("command_path: memory allocation error");
            return NULL;
        }

        // Get length of the command that was passed
        command_length = strlen(command);

        // Let's break down the path variable and get all the directories available
        path_token = strtok(path_copy, ":");

        while (path_token != NULL) {
            // Get the length of the directory
            directory_length = strlen(path_token);

            // Allocate memory for storing the command name together with the directory name
            file_path = malloc(command_length + directory_length + 2);

            if (!file_path) {
                perror("command_path: memory allocation error");
                free(path_copy);
                return NULL;
            }

            // Build the path for the command
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);

            // Test if this file path actually exists and return it if it does
            if (stat(file_path, &buffer) == 0) {
                // Free up allocated memory before returning the file_path
                free(path_copy);
                return file_path;
            } else {
                // Free up the file_path memory so we can check for another path
                free(file_path);
                path_token = strtok(NULL, ":");
            }
        }

        // If we don't get any file_path that exists for the command, return NULL
        free(path_copy);

        // Before we exit without luck, let's see if the command itself is a file_path that exists
        if (stat(command, &buffer) == 0) {
            return strdup(command);
        }

        return NULL;
    }

    return NULL;
}
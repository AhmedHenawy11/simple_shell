#include "main.h"


void change_directory(const char *directory) {
    char *new_directory;

    if (directory == NULL || strcmp(directory, "-") == 0) {
        // If no argument or argument is "-", change to the home directory
        new_directory = getenv("HOME");
        if (new_directory == NULL) {
            perror("cd: HOME not set");
            return;
        }
    } else {
        new_directory = (char *)directory;
    }

    char *current_directory = getcwd(NULL, 0);

    if (current_directory == NULL) {
        perror("cd: getcwd failed");
        return;
    }

    if (chdir(new_directory) == -1) {
        perror("cd");
    } else {
        // Update the PWD environment variable
        if (setenv("PWD", getcwd(NULL, 0), 1) == -1) {
            perror("cd: setenv failed");
        }

        // Add the command to the history
        add_to_history(new_directory);
    }

    free(current_directory);
}
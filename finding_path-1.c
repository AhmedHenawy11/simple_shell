#include "main.h"



char *search_directories(char *path_copy, char *command, int command_length) {
    char *path_token, *file_path;

    path_token = strtok(path_copy, ":");
    while (path_token != NULL) {
        file_path = build_file_path(path_token, command, command_length);

        if (file_path) {
            return file_path;
        } else {
            free(file_path);
            path_token = strtok(NULL, ":");
        }
    }

    return check_command_path(command);
}
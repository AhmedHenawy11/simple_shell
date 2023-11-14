#include "main.h"


char *build_file_path(char *path_token, char *command, int command_length) {
    int directory_length = strlen(path_token);
    char *file_path = malloc(command_length + directory_length + 2);

    if (!file_path) {
        perror("build_file_path: memory allocation error");
        return NULL;
    }

    strcpy(file_path, path_token);
    strcat(file_path, "/");
    strcat(file_path, command);

    struct stat buffer;
    if (stat(file_path, &buffer) == 0) {
        return file_path;
    } else {
        free(file_path);
        return NULL;
    }
}


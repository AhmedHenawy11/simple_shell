#include "main.h"
#include <sys/stat.h>

char *command_path(char *command) {
    char *path_copy = get_path_copy();
    if (!path_copy) {
        return NULL;
    }

    int command_length = strlen(command);
    char *file_path = search_directories(path_copy, command, command_length);

    free(path_copy);
    return file_path;
}

char *check_command_path(char *command) {
    struct stat buffer;
    if (stat(command, &buffer) == 0) {
        return strdup(command);
    }

    return NULL;
}
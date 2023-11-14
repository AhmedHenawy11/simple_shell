#include "main.h"


char *get_path_copy() {
    char *path = getenv("PATH");

    if (path) {
        char *path_copy = strdup(path);

        if (!path_copy) {
            perror("get_path_copy: memory allocation error");
            return NULL;
        }

        return path_copy;
    }

    return NULL;
}


#include "main.h"



char *get_user_input_line() {
    char *user_input_line = NULL;
    size_t len = 0;
    ssize_t input_length = getline(&user_input_line, &len, stdin);

    if (input_length == -1) {
        printf("Shell terminated\n");
        free(user_input_line);
        exit(EXIT_FAILURE);
    }

    return user_input_line;
}
#include "main.h"


char **tokenize_user_input(char *user_input_line, int *tokens) {
    char *user_input_cpy = malloc(sizeof(char) * strlen(user_input_line));
    if (user_input_cpy == NULL) {
        perror("tsh: memory allocation error");
        free(user_input_line);
        exit(EXIT_FAILURE);
    }
    strcpy(user_input_cpy, user_input_line);

    char *token = strtok(user_input_line, " \n");
    while (token != NULL) {
        (*tokens)++;
        token = strtok(NULL, " \n");
    }
    (*tokens)++;

    char **cmd_argv = malloc(sizeof(char *) * (*tokens));

    token = strtok(user_input_cpy, " \n");
    for (int i = 0; token != NULL; i++) {
        cmd_argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(cmd_argv[i], token);
        token = strtok(NULL, " \n");
    }
    cmd_argv[*tokens - 1] = NULL;

    free(user_input_cpy);
    return cmd_argv;
}

void free_cmd_argv(char **cmd_argv, int tokens) {
    for (int i = 0; i < tokens; i++) {
        free(cmd_argv[i]);
    }
    free(cmd_argv);
}

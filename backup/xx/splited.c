#include "main.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_TOKENS 100

void print_prompt(const char *prompt) {
    printf("%s", prompt);
}

ssize_t get_user_input(char **user_input_line, size_t *len) {
    return getline(user_input_line, len, stdin);
}

char **tokenize_input(char *user_input_line, int *tokens) {
    const char *string_separator = " \n";
    char *token;
    char **argv = malloc(sizeof(char *) * MAX_TOKENS);
    int i;
    if (!argv) {
        perror("tsh: memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (i = 0, token = strtok(user_input_line, string_separator); token != NULL; i++) {
        argv[i] = malloc(strlen(token) + 1);

        if (!argv[i]) {
            perror("tsh: memory allocation error");
            exit(EXIT_FAILURE);
        }

        strcpy(argv[i], token);
        token = strtok(NULL, string_separator);
    }

    *tokens = MAX_TOKENS;
    argv[MAX_TOKENS - 1] = NULL; /* Ensure the last element is NULL */

    return argv;
}

void free_tokens(char **argv) {
    int i;
    for (i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
    }
    free(argv);
}

int main(void) {
    char *shell_symbol = "(Henawy's_shell) $ ";
    char *user_input_line = NULL;
    size_t len = 0;
    ssize_t input_length = 0;
    int tokens, i;

    char **tokenized_input;

    while (1) {
        /* Print the shell prompt and get user input */
        print_prompt(shell_symbol);
        input_length = get_user_input(&user_input_line, &len);

        if (input_length == -1) {
            printf("Shell terminated\n");
            return EXIT_FAILURE;
        }

        /* Tokenize the user input */
        tokenized_input = tokenize_input(user_input_line, &tokens);

        /* Process the tokens as needed (printing in this example) */
        for (i = 0; tokenized_input[i] != NULL; i++) {
            printf("%s\n", tokenized_input[i]);
        }
        execmd(tokenized_input);
        /* Free memory allocated for tokens */
        free_tokens(tokenized_input);

        /* Free memory for user input line */
        free(user_input_line);
        user_input_line = NULL;
    }

    return EXIT_SUCCESS;
}
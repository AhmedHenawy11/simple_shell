#include "main.h"

int main(void) {
    char *shell_symbol = "(Henawy's_shell) $ ";
    char *user_input_line = NULL, *user_input_cpy = NULL;
    const char *string_seperator = " \n";
    size_t len = 0;
    ssize_t input_length = 0;
    int tokens = 0, i;
    char *token;

    while (1) {
        // printing shell prompt and taking command input.
        printf("%s", shell_symbol);
        input_length = getline(&user_input_line, &len, stdin);
        if (input_length == -1) {
            printf("Shell terminated\n");
            free(user_input_line);  // Free memory before returning
            return -1;
        }

        // making a copy of user input
        user_input_cpy = malloc(sizeof(char) * input_length);
        if (user_input_cpy == NULL) {
            perror("tsh: memory allocation error");
            free(user_input_line);  // Free memory before returning
            return -1;
        }
        strcpy(user_input_cpy, user_input_line);

        // getting the number of tokens:
        token = strtok(user_input_line, string_seperator);
        while (token != NULL) {
            tokens++;
            token = strtok(NULL, string_seperator);
        }
        tokens++;

        // storing each token in array
        char **cmd_argv = malloc(sizeof(char *) * tokens);

        token = strtok(user_input_cpy, string_seperator);

        for (i = 0; token != NULL; i++) {
            cmd_argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(cmd_argv[i], token);

            token = strtok(NULL, string_seperator);
        }
        cmd_argv[i] = NULL;

        // executing command in a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            free(user_input_line);  // Free memory before returning
            free(user_input_cpy);
            for (i = 0; cmd_argv[i] != NULL; i++) {
                free(cmd_argv[i]);
            }
            free(cmd_argv);
            return -1;
        } else if (pid == 0) {
            // This is the child process
            execmd(cmd_argv);
            // If execve fails, print an error and exit
            perror("Execution failed");
            exit(EXIT_FAILURE);
        } else {
            // This is the parent process
            int status;
            waitpid(pid, &status, 0);
        }

        if (user_input_line != NULL) {
            free(user_input_line);
            user_input_line = NULL;
        }
        free(user_input_cpy);
        for (i = 0; cmd_argv[i] != NULL; i++) {
            free(cmd_argv[i]);
        }
        free(cmd_argv);
    }

    return 0;
}
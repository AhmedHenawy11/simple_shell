#include "main.h"


void execmd(char **argv) {
    char *cmd = NULL, *actual_command = NULL;

    if (argv) {
        cmd = argv[0];
        actual_command = command_path(cmd);
        if (actual_command == NULL) {
            fprintf(stderr, "%s: %d: %s: not found\n", argv[0], getpid(), cmd);
            exit(EXIT_FAILURE);
        }

        if (execve(actual_command, argv, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
}

void free_cmd_argv(char **cmd_argv, int tokens) {
    for (int i = 0; i < tokens; i++) {
        free(cmd_argv[i]);
    }
    free(cmd_argv);
}

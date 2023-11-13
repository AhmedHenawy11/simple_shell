#include "main.h"


void execmd(char **argv) {
    char *cmd = NULL, *actual_command = NULL;

    if (argv) {
        cmd = argv[0];
        actual_command = command_path(cmd);
        if (execve(actual_command, argv, NULL) == -1) {
            perror("Not found:");
        }
    }
}
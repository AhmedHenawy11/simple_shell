#include "main.h"


void execute_command(char *user_input_line, char **cmd_argv, int tokens) {
    if (strlen(user_input_line) > 1) {
        // Add the command to the history
        add_to_history(user_input_line);

        // Check if the command is "cd"
        if (strcmp(cmd_argv[0], "cd") == 0) {
            if (cmd_argv[1] != NULL) {
                change_directory(cmd_argv[1]);
            } else {
                // If no argument is given, change to the home directory
                change_directory(NULL);
            }
        } else if (strcmp(user_input_line, "history\n") == 0) {
            display_history();
        } else if (strcmp(cmd_argv[0], "exit") == 0) {
            terminate_shell();
        } else {
            // executing command in a child process
            pid_t pid = fork();

            if (pid == -1) {
                perror("Fork failed");
                free(user_input_line);
                free_cmd_argv(cmd_argv, tokens);
                exit(EXIT_FAILURE);
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
        }
    }
}
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_HISTORY_SIZE 10

char *command_history[MAX_HISTORY_SIZE];
int history_count = 0;

void add_to_history(const char *command) {
    if (history_count == MAX_HISTORY_SIZE) {
        free(command_history[0]);
        for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
            command_history[i] = command_history[i + 1];
        }
        history_count--;
    }
    command_history[history_count++] = strdup(command);
}

void display_history() {
    printf("Command History:\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, command_history[i]);
    }
}

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

char *command_path(char *command) {
    char *path, *path_copy, *path_token, *file_path;
    int command_length, directory_length;
    struct stat buffer;

    // Get the PATH environment variable
    path = getenv("PATH");

    if (path) {
        // Duplicate the path string
        path_copy = strdup(path);

        if (!path_copy) {
            perror("get_executable_path: memory allocation error");
            return NULL;
        }

        // Get length of the command that was passed
        command_length = strlen(command);

        // Let's break down the path variable and get all the directories available
        path_token = strtok(path_copy, ":");

        while (path_token != NULL) {
            // Get the length of the directory
            directory_length = strlen(path_token);

            // Allocate memory for storing the command name together with the directory name
            file_path = malloc(command_length + directory_length + 2);

            if (!file_path) {
                perror("get_executable_path: memory allocation error");
                free(path_copy);
                return NULL;
            }

            // Build the path for the command
            strcpy(file_path, path_token);
            strcat(file_path, "/");
            strcat(file_path, command);

            // Test if this file path actually exists and return it if it does
            if (stat(file_path, &buffer) == 0) {
                // Free up allocated memory before returning the file_path
                free(path_copy);
                return file_path;
            } else {
                // Free up the file_path memory so we can check for another path
                free(file_path);
                path_token = strtok(NULL, ":");
            }
        }

        // If we don't get any file_path that exists for the command, return NULL
        free(path_copy);

        // Before we exit without luck, let's see if the command itself is a file_path that exists
        if (stat(command, &buffer) == 0) {
            return strdup(command);
        }

        return NULL;
    }

    return NULL;
}


void change_directory(const char *directory) {
    char *new_directory;

    if (directory == NULL || strcmp(directory, "-") == 0) {
        // If no argument or argument is "-", change to the home directory
        new_directory = getenv("HOME");
        if (new_directory == NULL) {
            perror("cd: HOME not set");
            return;
        }
    } else {
        new_directory = (char *)directory;
    }

    char *current_directory = getcwd(NULL, 0);

    if (current_directory == NULL) {
        perror("cd: getcwd failed");
        return;
    }

    if (chdir(new_directory) == -1) {
        perror("cd");
    } else {
        // Update the PWD environment variable
        if (setenv("PWD", getcwd(NULL, 0), 1) == -1) {
            perror("cd: setenv failed");
        }

        // Add the command to the history
        add_to_history(new_directory);
    }

    free(current_directory);
}

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
            free(user_input_line);
            return -1;
        }

        user_input_cpy = malloc(sizeof(char) * input_length);
        if (user_input_cpy == NULL) {
            perror("tsh: memory allocation error");
            free(user_input_line);
            return -1;
        }
        strcpy(user_input_cpy, user_input_line);

        token = strtok(user_input_line, string_seperator);
        while (token != NULL) {
            tokens++;
            token = strtok(NULL, string_seperator);
        }
        tokens++;

        char **cmd_argv = malloc(sizeof(char *) * tokens);

        token = strtok(user_input_cpy, string_seperator);

        for (i = 0; token != NULL; i++) {
            cmd_argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(cmd_argv[i], token);

            token = strtok(NULL, string_seperator);
        }
        cmd_argv[i] = NULL;

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
            } else {
                // executing command in a child process
                pid_t pid = fork();

                if (pid == -1) {
                    perror("Fork failed");
                    free(user_input_line);
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
            }
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
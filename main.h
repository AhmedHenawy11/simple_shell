#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAX_HISTORY_SIZE 10




void execmd(char **argv);
char *command_path(char *command);
char *get_path_copy();
char *search_directories(char *path_copy, char *command, int command_length);
char *build_file_path(char *path_token, char *command, int command_length);
char *check_command_path(char *command);

void change_directory(const char *directory);
void add_to_history(const char *command);
void display_history(void);
void terminate_shell(void);
void free_cmd_argv(char **cmd_argv, int tokens);
void shell_sympol(void);
char *get_user_input_line();
char **tokenize_user_input(char *user_input_line, int *tokens);
void execute_command(char *user_input_line, char **cmd_argv, int tokens);

#endif


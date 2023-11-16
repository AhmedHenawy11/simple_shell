#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAX_HISTORY_SIZE 10


extern char **environ;


void execmd(char **argv);
char *command_path(char *command);
char *get_path_copy();
char *search_directories(char *path_copy, char *command, int command_length);
char *build_file_path(char *path_token, char *command, int command_length);
char *check_command_path(char *command);

void change_directory(const char *directory);
void terminate_shell(void);
void free_cmd_argv(char **cmd_argv);
void shell_sympol(void);
char *get_user_input_line();
char **tokenize_user_input(char *user_input_line, int *tokens);
void execute_command(char *user_input_line, char **cmd_argv, int tokens);
void print_environment(void);

char *_strdup(char *str);
size_t _strlen(const char *str);
int _putchar(char c);
int _strcasecmp(const char *s1, const char *s2);

char *_getenv(const char *name);
char *_strcpy(char *dest, const char *src);

char *_strcat(char *dest, const char *src);

int _strcmp(const char *s1, const char *s2);
int _fprintf(FILE *stream, const char *format, ...);


int _printf(const char *format, ...);


#endif


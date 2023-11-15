#include "main.h"

/**
 * tokenize_user_input - spliting each word of input line and,
 *  taking it as token by seperator
 * description: this functions s splitting the command into tokens
 * to execute each one,
 * after storing each token in array of strings
 * @user_input_line: the line before
 * @tokens: number of tokens
 * Return: the array of strings that hold the actual commands
 */

char **tokenize_user_input(char *user_input_line, int *tokens)
{
    char *user_input_cpy = strdup(user_input_line);
    char **cmd_argv, *token;
    int i = 0;

    if (!user_input_cpy)
    {
        perror("tsh: memory allocation error");
        free(user_input_line);
        exit(EXIT_FAILURE);
    }

    token = strtok(user_input_cpy, " \n");
    for (; token != NULL; i++, (*tokens)++, token = strtok(NULL, " \n"))
        continue;

    cmd_argv = malloc(sizeof(char *) * (*tokens + 1));  
    if (!cmd_argv)
    {
        perror("tsh: memory allocation error");
        free(user_input_cpy);
        exit(EXIT_FAILURE);
    }

    strcpy(user_input_cpy, user_input_line);
    token = strtok(user_input_cpy, " \n");
    for (i = 0; token != NULL; i++, token = strtok(NULL, " \n"))
    {
        size_t token_length = strlen(token);
        cmd_argv[i] = malloc(token_length + 1);
        if (!cmd_argv[i])
        {
            perror("tsh: memory allocation error");
            free(user_input_cpy);
            free_cmd_argv(cmd_argv, i);
            exit(EXIT_FAILURE);
        }
        strcpy(cmd_argv[i], token);
    }
    cmd_argv[i] = NULL;

    free(user_input_cpy);
    return cmd_argv;
}
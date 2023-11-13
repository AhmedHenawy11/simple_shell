#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **argv)
{
    char *shell_symbol = "(Henawy's_shell) $ ";
    char *user_input_line = NULL, *user_input_cpy = NULL;
    const char *string_seperator = " \n";
    size_t len = 0;
    ssize_t input_length = 0;
    int tokens = 0, i;
    char *token;

    (void) ac;

    while(1)
    {
////////////// printing shell prpmpet and taking commant input.
        printf("%s", shell_symbol);
        input_length = getline(&user_input_line, &len, stdin);
        if (input_length == (-1))
        {
            printf("Shell terminated\n");
            return (-1);
        }
//////////////// making the copy of user input
        user_input_cpy = malloc(sizeof(char) * input_length);
        if (user_input_cpy == NULL)
        {
            perror("tsh: memory allocation error");
            return (-1);
        }
        strcpy(user_input_cpy, user_input_line);
////// getting the number of tokens:
        token = strtok(user_input_line, string_seperator);
        while (token != NULL)
        {
            tokens++;
            token = strtok(NULL, string_seperator);
        }
        tokens++;

////////////////////////////////////  storing each token in array
        argv = malloc(sizeof(char *) * tokens);

        token = strtok(user_input_cpy, string_seperator);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, string_seperator);
        }
        argv[i] = NULL;
    //executing command
        execmd(argv);




        printf("%s\n",user_input_line);
        if (user_input_line != NULL)
        {
            free(user_input_line);
            user_input_line = NULL; 
        }
        free(user_input_cpy);
    }
    return (0);
}

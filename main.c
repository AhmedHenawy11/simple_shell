#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **argv)
{
    char *shell_symbol = "(Henawy's_shell) $ ";
    char *user_input_line = NULL;
    size_t len = 0;

    (void)ac; (void)argv;


    printf("%s", shell_symbol);
    getline(&user_input_line, &len, stdin);
    printf("%s\n",user_input_line);
    free(user_input_line);

    return (0);
}
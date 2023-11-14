#include "main.h"

int main(void) {
    while (1) {
        shell_sympol();

        char *user_input_line = get_user_input_line();
        int tokens = 0;
        char **cmd_argv = tokenize_user_input(user_input_line, &tokens);

        execute_command(user_input_line, cmd_argv, tokens);

        free(user_input_line);
        free_cmd_argv(cmd_argv, tokens);
    }

    return 0;
}
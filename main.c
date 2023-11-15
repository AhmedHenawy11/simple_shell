#include "main.h"

/**
 * main - The main function of the  (Henawy's_shell).
 *
 * Description: runs an interactive shell,
 * continuously prompting the user forcommands,
 * splitting them, and executing the corresponding actions.
 * Return: terminating the shell.
 */

int main(void)
{
	char *user_input_line;
	int tokens;
	char **cmd_argv;

	while (1)
	{
		shell_sympol();

		user_input_line = get_user_input_line();
		tokens = 0;
		cmd_argv = tokenize_user_input(user_input_line, &tokens);

		execute_command(user_input_line, cmd_argv, tokens);

		free(user_input_line);
		free_cmd_argv(cmd_argv, tokens);
	}

	return (0);
}

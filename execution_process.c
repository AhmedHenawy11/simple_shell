#include "main.h"
/**
 * execute_command - Execute the provided command based on user input.
 * @user_input_line: The user's input line.
 * @cmd_argv:       The tokenized command arguments.
 * @tokens:          The number of tokens in cmd_argv.
 */
void execute_command(char *user_input_line, char **cmd_argv, int tokens)
{
	if (strlen(user_input_line) > 1)
	{
		if (strcmp(cmd_argv[0], "cd") == 0)
		{
			// ... (unchanged)
		}
		else if (strcmp(cmd_argv[0], "exit") == 0)
		{
			terminate_shell();
		}
		else if (strcmp(cmd_argv[0], "env") == 0)
		{
			print_environment();
		}
		else
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("Fork failed");
				free(user_input_line);
				free_cmd_argv(cmd_argv, tokens);
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execmd(cmd_argv);
				perror("Execution failed");

				// Add an error message for command not found
				fprintf(stderr, "%s: command not found\n", cmd_argv[0]);

				exit(EXIT_FAILURE);
			}
			else
			{
				int status;
				waitpid(pid, &status, 0);
			}
		}
	}
}

#include "main.h"


void change_directory(const char *directory)
{
    char *new_directory;
    char *current_directory = getcwd(NULL, 0);
    
    if (directory == NULL || strcmp(directory, "-") == 0)
    {
        new_directory = getenv("HOME");
        if (new_directory == NULL)
        {
            perror("cd: HOME not set");
            return;
        }
    } else
    {
        new_directory = (char *)directory;
    }

    if (current_directory == NULL)
    {
        perror("cd: getcwd failed");
        return;
    }

    if (chdir(new_directory) == -1)
    {
        perror("cd");
    } else
    {
        if (setenv("PWD", getcwd(NULL, 0), 1) == -1) {
            perror("cd: setenv failed");
        }
    }

    free(current_directory);
}


char *check_command_path(char *command)
{
	struct stat buffer;

	if (stat(command, &buffer) == 0)
	{
		return (strdup(command));
	}

	return (NULL);
}

char *command_path(char *command)
{
	char *path_copy = get_path_copy();
	int command_length = strlen(command);
	char *file_path = search_directories(path_copy, command, command_length);

	if (!path_copy)
	{
		return (NULL);
	}

	free(path_copy);
	return (file_path);
}

void free_cmd_argv(char **cmd_argv, int tokens)
{
	for (int i = 0; i < tokens; i++)
	{
		free(cmd_argv[i]);
	}
	free(cmd_argv);
}



void execmd(char **argv)
{
	char *cmd = NULL, *actual_command = NULL;

	if (argv)
	{
		cmd = argv[0];
		actual_command = command_path(cmd);
		if (actual_command == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], getpid(), cmd);
			exit(EXIT_FAILURE);
		}

		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}


void execute_command(char *user_input_line, char **cmd_argv, int tokens)
{
	if (strlen(user_input_line) > 1)
	{
		if (strcmp(cmd_argv[0], "cd") == 0)
		{
			if (cmd_argv[1] != NULL)
			{
				change_directory(cmd_argv[1]);
			} else
			{
				change_directory(NULL);
			}
		} else if (strcmp(cmd_argv[0], "exit") == 0)
		{
			terminate_shell();
		} else if (strcmp(cmd_argv[0], "env") == 0)
		{
			print_environment();
		} else
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("Fork failed");
				free(user_input_line);
				free_cmd_argv(cmd_argv, tokens);
				exit(EXIT_FAILURE);
			} else if (pid == 0)
			{
				execmd(cmd_argv);
				perror("Execution failed");
				exit(EXIT_FAILURE);
			} else
			{
				int status;

				waitpid(pid, &status, 0);
			}
		}
	}
}



char *search_directories(char *path_copy, char *command, int command_length)
{
	char *path_token, *file_path;

	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		file_path = build_file_path(path_token, command, command_length);

		if (file_path)
		{
			return (file_path);
		}
			free(file_path);
			path_token = strtok(NULL, ":");
	}

	return (check_command_path(command));
}


char *get_path_copy()
{
	char *path = getenv("PATH");

	if (path)
	{
		char *path_copy = strdup(path);

		if (!path_copy)
		{
			perror("get_path_copy: memory allocation error");
			return (NULL);
		}

		return (path_copy);
	}

	return (NULL);
}


char *build_file_path(char *path_token, char *command, int command_length)
{
	int directory_length = strlen(path_token);
	char *file_path = malloc(command_length + directory_length + 2);

	if (!file_path)
	{
		perror("build_file_path: memory allocation error");
		return (NULL);
	}

	strcpy(file_path, path_token);
	strcat(file_path, "/");
	strcat(file_path, command);

	struct stat buffer;

	if (stat(file_path, &buffer) == 0)
	{
		return (file_path);
	}
	free(file_path);
	return (NULL);
}


void print_environment(void)
{
	for (char **env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}


char **tokenize_user_input(char *user_input_line, int *tokens)
{
	char *user_input_cpy = malloc(sizeof(char) * strlen(user_input_line));

	if (user_input_cpy == NULL)
	{
		perror("tsh: memory allocation error");
		free(user_input_line);
		exit(EXIT_FAILURE);
	}
	strcpy(user_input_cpy, user_input_line);
	char *token = strtok(user_input_line, " \n");

	while (token != NULL)
	{
		(*tokens)++;
		token = strtok(NULL, " \n");
	}
	(*tokens)++;
	char **cmd_argv = malloc(sizeof(char *) * (*tokens));

	token = strtok(user_input_cpy, " \n");
	for (int i = 0; token != NULL; i++)
	{
		cmd_argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(cmd_argv[i], token);
		token = strtok(NULL, " \n");
	}
	cmd_argv[*tokens - 1] = NULL;
	free(user_input_cpy);
	return (cmd_argv);
}


void terminate_shell(void)
{
	exit(EXIT_SUCCESS);
}

void shell_sympol(void)
{
	printf("(Henawy's_shell)$ ");
}


char *get_user_input_line()
{
	char *user_input_line = NULL;
	size_t len = 0;
	ssize_t input_length = getline(&user_input_line, &len, stdin);

	if (input_length == -1)
	{
		printf("Shell terminated\n");
		free(user_input_line);
		exit(EXIT_FAILURE);
	}

	return (user_input_line);
}

int main(void)
{
	while (1)
	{
		shell_sympol();

		char *user_input_line = get_user_input_line();
		int tokens = 0;
		char **cmd_argv = tokenize_user_input(user_input_line, &tokens);

		execute_command(user_input_line, cmd_argv, tokens);

		free(user_input_line);
		free_cmd_argv(cmd_argv, tokens);
	}

	return (0);
}
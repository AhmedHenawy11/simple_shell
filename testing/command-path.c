#include "main.h"
#include <sys/stat.h>

/**
 * command_path - executing the finding file path process
 * @command: the command which finding path searching for
 * Return: file path if success
 */


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

/**
 * check_command_path - checking command before passing it
 * @command: the command which finding path searching for
 * Return: command path if success
 */
char *check_command_path(char *command)
{
	struct stat buffer;

	if (stat(command, &buffer) == 0)
	{
		return (strdup(command));
	}

	return (NULL);
}

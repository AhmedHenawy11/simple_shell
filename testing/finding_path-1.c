#include "main.h"

/**
 * search_directories - the name explains
 * description: search for bath after taking command and the file path_copy
 * Return: the input line
 * @command: the input cmd
 * @command_length: length
 * @path_copy: the copy of path
 */


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

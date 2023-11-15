#include "main.h"

/**
 * change_directory - executing the change directory command (cd)
 * @directory: name of directory
 * Return: directory if success
 */

void change_directory(const char *directory)
{
	char *new_directory;
	char *current_directory = getcwd(NULL, 0);

	if (directory == NULL || _strcmp(directory, "-") == 0)
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
		if (setenv("PWD", getcwd(NULL, 0), 1) == -1)
			perror("cd: setenv failed");
	}

	free(current_directory);
}

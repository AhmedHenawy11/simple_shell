#include "main.h"

/**
 * get_path_copy - making a copy of the file path
 * description: the name of the function explains
 * Return: tpath on success or null
 */
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

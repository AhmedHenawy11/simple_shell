#include "main.h"


/**
 * print_environment - the name of explains
 * Return: void
 */

void print_environment(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}

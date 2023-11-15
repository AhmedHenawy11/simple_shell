#include "main.h"


/**
 * print_environment - the name of explains
 * Return: void
 */


void print_environment(void)
{
	for (char **env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}

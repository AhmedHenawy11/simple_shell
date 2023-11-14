#include "main.h"
	char *command_history[MAX_HISTORY_SIZE];
	int history_count = 0;

/**
 * add_to_history - recording function
 * description: record the history of commands
 * @command: command
 * Return: void
 */

void add_to_history(const char *command)
{


	if (history_count == MAX_HISTORY_SIZE)
	{
		free(command_history[0]);
		for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++)
		{
			command_history[i] = command_history[i + 1];
		}
		history_count--;
	}
	command_history[history_count++] = strdup(command);
}

/**
 * display_history - the name of the function explains
 * Return: void
 */

void display_history(void)
{
	char *command_history[MAX_HISTORY_SIZE];
	int history_count = 0;

	printf("Command History:\n");
	for (int i = 0; i < history_count; i++)
	{
		printf("%d: %s\n", i + 1, command_history[i]);
	}
}

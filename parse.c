#include "shell.h"

/**
 * parseInput - parses the input command
 * @input: input command
 * @args: array of input
 * Return: 0
 */

void parseInput(char *input, char *args[])
{
	char *token;
	int argCount = 0;

	token = strtok(input, " ");
	while (token != NULL && argCount < MAX_ARGS - 1)
	{
		args[argCount] = token;
		argCount++;
		token = strtok(NULL, " ");
	}
	args[argCount] = NULL;
}


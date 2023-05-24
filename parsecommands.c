#include "shell.h"

/**
 * parseCommands - parse commands
 * @input: user command input
 * @commands: commands separated
 * Return: void
 */

void parseCommands(char *input, char **commands)
{
	int commandIndex = 0;
	char *token = strtok(input, ";");

	while (token != NULL)
	{
		 commands[commandIndex++] = token;
		 token = strtok(NULL, ";");
	}
	 commands[commandIndex] = NULL; /* Null-terminate the commands array */
}

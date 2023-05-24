#include "shell.h"

void parseCommands(char *input, char **commands)
{
	int commandIndex = 0;
	char *token = strtok(input, ";");

	 while(token != NULL)
	 {
		 commands[commandIndex++] = token;
		 token = strtok(NULL, ";");
	 }
	 commands[commandIndex] = NULL; /* Null-terminate the commands array */
}

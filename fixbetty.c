#include "shell.h"

/**
* freePointers - free pointers
* @line: line
* @path: absolute path
* @arguments: arguments
* Return: Noting
*/
void freePointers(char *line, char *path, char **arguments)
{
	if (line != path && path != arguments[0])
	{
		free(path);
	}
	free(arguments);
	free(line);
}

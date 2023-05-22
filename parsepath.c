#include "shell.h"

int parsePath(const char *path, char *directories[])
{
	int count = 0;
	char *path_copy;
	char *token;

	/* Create a copy of the path string */
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		exit (EXIT_FAILURE);
	}

	/* Tokenize the path using ":" as the delimiter */
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		directories[count++] = strdup(token);
		token = strtok(NULL, ":");
	}
	/* set the last element to NULL */
	directories[count] = NULL;

	/* free the allocated memory for the path copy */
	free(path_copy);

	return (count);
}



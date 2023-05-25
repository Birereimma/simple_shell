#include "shell.h"

/**
 * changeDirectory - changes directory
 * @directory: specified directory
 * Return: void
 */

void changeDirectory(char *directory)
{
	char *prevDir = getenv("PWD"); /*  Get the current working directory */
	char cwd[MAX_INPUT_SIZE];

	if (strcmp(directory, "-") == 0)
	{
		/* chane to the previous directory */
		directory = getenv("OLDPWD");
		if (directory == NULL)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		}
	}
	if (chdir(directory) == 0)
	{
		getcwd(cwd, sizeof(cwd)); /* Get the new current working directory */
		setenv("OLDPWD", prevDir, 1); /* Update the OLDPWD environment variable */
		setenv("PWD", cwd, 1); /* Update the PWD environment variable */
	}
	else
	{
		write(STDERR_FILENO, "cd: error changing directory\n", 29);
	}
	if (strcmp(prevDir, cwd) != 0)
	{
		write(STDOUT_FILENO, cwd, strlen(cwd)); /* Print the current directory */
		write(STDOUT_FILENO, "\n", 1); /* Print a newline character */
	}
}

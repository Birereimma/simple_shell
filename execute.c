#include "shell.h"

/**
 * executeCommand - executing the input command
 * @args: array of command
 * Return: always success
 */

void executeCommand(char *args[])
{
	pid_t child_pid;
	int status;

	/* fork a child process to execute the command */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0) /* child process */
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* parent process */
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}

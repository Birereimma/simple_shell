#include "shell.h"

extern char *environ;
/**
 * main - entry point of the program
 *
 * Return: 0 on success, 1 on fail
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
	const char prompt[] = "$ ";
	char *args[MAX_ARGS];
	char *directories[MAX_DIRS];
	char *path;
	int numDirs;
	char *executablePath;
	pid_t pid;

	/* get the value of path from the environment */
	path = getenv("PATH");

	/*plit the path into directories */
	numDirs = parsePath(path, directories);

	while(1)
	{
		/* display a propt */
		write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);

		/* read user input */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			/* print a new line if EOF is entered */
			if (feof(stdin))
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		/* remove the new character from the end of the input replace it with a null terminator */
		input[strcspn(input, "\n")] = '\0';

		parseInput(input, args);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				break;
			}
			else if (strcmp(args[0], "env") == 0)
			{
					/* Handle the env command */
					 const char** env = (const char**)environ;
					 while(*env != NULL)
					 {
						 /* Print each environment variable */
						 write(STDOUT_FILENO, *env, strlen(*env));
						 write(STDOUT_FILENO, "\n", 1);
						 env++;
					 }
			}
			else
			{
				executablePath = findExecutable(args[0], directories, numDirs);
				if (executablePath != NULL)
				{
					pid = fork();
					if (pid < 0)
					{
						perror("forking erro");
					}
					else if (pid == 0)
					{
						/* child process */
						execve(executablePath, args, (char *const *)environ);
						perror("Command execution error");
						_exit(1);
					}
					else
					{
						/* parent process */
						wait(NULL);
					}
					free(executablePath);
				}
				else
				{
					write(STDOUT_FILENO, "Command not found: ", 19);
					write(STDOUT_FILENO, args[0], strlen(args[0]));
					write(STDOUT_FILENO, "\n", 1);
				}
			}
		}
	}
	return (0);
}

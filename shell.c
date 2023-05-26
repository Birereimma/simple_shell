#include "shell.h"

/**
 * main - entry point of the program
 * @argc: arguments count
 * @argv: arguments in the command
 *
 * Return: 0 on success, 1 on fail
 */

extern char **environ;

int main(int argc, char *argv[])
{
	char input[MAX_INPUT_SIZE];
	const char prompt[] = "$ ";
	char *args[MAX_ARGS];
	char *directories[MAX_DIRS];
	char *path;
	char *executablePath;
	pid_t pid;
	char *homeDir;
	char *commands[MAX_COMMANDS];
	int i, interactive, numDirs, argCount, exitStatus;
	FILE *file;

	if (argc > 1)
	{
		file = fopen(argv[1], "r");/* Non-interactive mode */
		if (file == NULL)
		{
			perror("fopen");
			exit(EXIT_SUCCESS);
		}
		while (fgets(input, sizeof(input), file) != NULL)
		{
			input[strcspn(input, "\n")] = '\0';

			argCount = tokenizeInput(input, args);
			if (args[0] != NULL)
			{
				if (strcmp(args[0], "exit") == 0)
				{
					break;
				}
				else if (strcmp(args[0], "env") == 0)
				{
					const char **env = (const char **)environ;

					while (*env != NULL)
					{
						if (strncmp(*env, "PWD=", 4) != 0)/* Skip Print each environment variable */
                                        	{
							write(STDOUT_FILENO, *env, strlen(*env));
							write(STDOUT_FILENO, "\n", 1);
						}
						env++;
					}
                        	}
				else if (strcmp(args[0], "cd") == 0)
				{
					if (argCount == 1)
					{
						changeDirectory(getenv("HOME"));
					}
					else if (argCount == 2)
					{
						changeDirectory(args[1]);
					}
					else 
					{
						write(STDERR_FILENO, "cd: invalid usage\n", 18);
					}
				}
					else 
					{
						executeCommand(args);
					}
					memset(args, 0, MAX_ARGS * sizeof(char *));
			}
			fclose(file);
		}
	}
		else
		{
			/* get the value of path from the environment */
			path = getenv("PATH");

			/*plit the path into directories */
			numDirs = parsePath(path, directories);

			interactive = isatty(STDIN_FILENO);
			while (1)
			{
				if (interactive)
				{
					/* display a propt */
					write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
				}
				/* read user input using custom_getline */
				if (custom_getline(input, sizeof(input)) == -1)
				{
					perror("custom_getline");
					exit(EXIT_SUCCESS);
				}

				/* remove the new character from the end of the input replace it with a null terminator */
				if (input[strlen(input) - 1] == '\n')
				{
					input[strlen(input) - 1] = '\0';
				}

				/* Parse the input into commands */
				parseCommands(input, commands);

				/* Execute each command sequentially */
				for (i = 0; commands[i] != NULL; i++)
				{
					argCount = tokenizeInput(commands[i], args);
				}

				/* tokenize the input into arguments */
				argCount = tokenizeInput(input, args);
				if (argCount > 0)
				{
					if (strcmp(args[0], "exit") == 0)
					{
						/* Check if additional argument is provided for the exit command */
						if (argCount == 2)
						{
							exitStatus = atoi(args[1]);
							exit(exitStatus);
						}
						else
						{
							exit(EXIT_SUCCESS);
						}
					}
					else if (strcmp(args[0], "setenv") == 0)
					{
						if (argCount != 3)
						{
							write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", strlen("Usage: setenv VARIABLE VALUE\n"));
						}
						else
						{
							if (setenv(args[1], args[2], 1) != 0)
							{
								write(STDERR_FILENO, "Failed to set environment variable\n", strlen("Failed to set environment variable\n"));
							}
						}
					}	
					else if (strcmp(args[0], "unsetenv") == 0)
					{
						if (argCount != 2)
						{	
							write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", strlen("Usage: unsetenv VARIABLE\n"));
						}
						else
						{
							if (unsetenv(args[1]) != 0)
							{
								write(STDERR_FILENO, "Failed to unset environment variable\n", strlen("Failed to unset environment variable\n"));
							}
						}
					}
					else if (strcmp(args[0], "env") == 0)
					{
						/* Handle the env command */
						char **env = environ;
						while (*env != NULL)
						{
							/* Skip Print each environment variable */
							/*if (strncmp(*env, "PWD=", 4) != 0) */

							write(STDOUT_FILENO, *env, strlen(*env));
							write(STDOUT_FILENO, "\n", 1);
							env++;
						}
					}
					else if (strcmp(args[0], "cd") == 0)
					{
						/* handle the cd command */
						if (argCount == 1)
						{
							homeDir = getenv("HOME");
							changeDirectory(homeDir);
						}
						else if (argCount == 2)
						{
							/* argument provided, change to the specific directory */
							changeDirectory(args[1]);
						}
						else
						{
							write(STDERR_FILENO, "cd: invalid usage\n", 18);
						}
					}
					else
					{
						executeCommand(args);
					}
					executablePath = findExecutable(args[0], directories, numDirs);
					if (executablePath != NULL)
					{
						pid = fork();
						if (pid < 0)
						{
							perror("forking error");
							exit(EXIT_SUCCESS);
						}
						else if (pid == 0)
						{
							/* child process */
							execve(executablePath, args, (char *const *)environ);
							perror("Command execution error");
							exit(EXIT_SUCCESS);
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

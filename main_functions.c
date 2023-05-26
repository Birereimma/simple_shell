#include "shell.h"
#define _GNU_SOURCE
#include <errno.h>
#include <signal.h>

/**
* executeCommand - prompts a message and gets user input
* @command: user input comand
* @args: user command arguments
* @bt: list_builtin
* Return: integer
*/
int executeCommand(char *command, char **args, builtin *bt)
{
	builtin *bt_found = NULL;
	int pid = 0, status;

	bt_found = checkBuiltin(command, bt);
	if (bt_found != NULL)
		return (bt_found->function());
	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, __environ) == -1)
		{
			return (-1);
		}
	}
	else
		wait(&status);
	return (1);
}
/**
* prompt - prompts a message and gets user input
* @text: text to be displayed as prompt
* Return: arguments as input recieved
*/
char *prompt(char *text)
{
	char *line = NULL;
	size_t size = 0;
	int prompt_size = 0, i = 0;

	if (!text)
	{
		perror("Prompt message can't be NULL");
		return (NULL);
	}
	if (isatty(STDIN_FILENO) == 1)
	{
		prompt_size = stringSize(text);
		if (write(STDOUT_FILENO, text, prompt_size) == -1)
		{
			perror("t-sh");
		}
	}
	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\0')
	{
		if (line[i] == '\n' || line[i] == EOF)
		{
			line[i] = '\0';
		}
		i++;
	}
	return (line);
}
/**
* main - main function
* @argc: number of arguments
* @argv: input command arguments
* @env: environment
* Return: 0 always
*/
int main(int argc, char **argv, char **env)
{
	builtin bt[] = {
		{0, "env", printEnv},
		{1, "exit", exit_shell},
		{-1, NULL, NULL}
	};
	if (argc > 1)
	{
		printErrors(argv[0], argv[1], "Can't open ", 0, 1);
		return (-1);
	}
	signal(SIGINT, signintHandle);
	startLoop(bt, argv[0], env);
	return (0);
}
/**
* transArguments - transforms the arguments
* @ac: arguments
* @bt: builtin list
* @av: name of the program
* @c: amount of loops
* @env: environment
* Return: path to the command
*/
char *transArguments(char **ac, builtin *bt, char *av, int c, char **env)
{
	char *aux = NULL;
	struct stat statbuf;

	if (checkBuiltin(ac[0], bt) == NULL)
	{
		if (stat(ac[0], &statbuf) == -1)
		{
			aux = concatPath(ac[0], env);
			if (aux ==  NULL)
			{
				printErrors(av, ac[0], "not found\n", c, 0);
				return (NULL);
			} else if (*aux == 'A')
			{
				printErrordir(av, "No such file or directory");
				return (NULL);
			}
		} else
		{
			aux = ac[0];
		}
	} else
	{
		if (sizeDoubleptr(ac) > 1)
		{
			return (NULL);
		}
		aux = ac[0];
	}
	return (aux);
}

/**
* starLoop - starts the inifinite loop
* @bt: struct whit arguments builtin
* @argv: name of the program
* @env: environment
* Return: Noting
*/
void startLoop(builtin *bt, char *argv, char **env)
{
	int coun_loop = 0;
	char *line = NULL, **arguments = NULL, *path = NULL;

	while (++coun_loop)
	{
		line = prompt("$ ");
		if (!line)
		{
			if (isatty(STDIN_FILENO) != 0)
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		} else if (stringSize(line) == 0)
		{
			free(line);
			continue;
		}
		arguments = divideLine(line, " ");
		if (!arguments)
		{
			free(line);
			continue;
		}
		path = transArguments(arguments, bt, argv, coun_loop, env);
		if (path == NULL)
		{
			free(arguments);
			free(line);
			continue;
		}
		if (executeCommand(path, arguments, bt) == -1)
		{
			void freePointers(char *line, char *path, char **arguments);
			exit(EXIT_SUCCESS);
		}
		freePointers(line, path, arguments);
	}
}

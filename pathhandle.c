#include "shell.h"

/**
* concatPath - search for path
* @command: String to search
* @env: environment
* Return: Pointer to the string
*/
char *concatPath(char *command, char **env)
{
	char **paths = NULL, *concat = NULL;
	struct stat statbuf;
	int command_size = 0, path_size = 0, paths_size = 0, aux = 0;

	paths = dividePath("PATH", env);
	if (paths == NULL)
		return ("A");
	paths_size = sizeDoubleptr(paths);
	if (command)
		command_size = stringSize(command);
	while (aux < paths_size)
	{
		if (paths[aux])
			path_size = stringSize(paths[aux]);
		concat = malloc((path_size + command_size + 2) * sizeof(char));
		if (concat == NULL)
		{
			freeDoubleptr(paths);
			return (NULL);
		}
		concat[0] = '\0';
		concatString(concat, paths[aux], 0);
		concat[path_size] = '/';
		concat[path_size + 1] = '\0';
		concatString(concat, command, path_size + 1);
		concat[path_size + command_size + 1] = '\0';
		if (stat(concat, &statbuf) == 0)
		{
			freeDoubleptr(paths);
			return (concat);
		}
		free(concat);
		aux++;
	}
	freeDoubleptr(paths);
	return (NULL);
}

/**
* dividePath - divide to path in tokens
* @str: String to search
* @env: environment
* Return: Pointer to the string
*/

char **dividePath(char *str, char **env)
{
	char *_env = NULL, **PATH = NULL, **PATHS = NULL;
	char **aux = NULL;
	int size = 0;

	_env = _getenv(str, env);
	if (_env == NULL)
		return (NULL);
	PATH = divideLine(_env, "=");
	if (!PATH)
	{
		free(_env);
		return (NULL);
	}
	PATHS = divideLine(PATH[1], ":");
	if (!PATHS || PATHS[0] == NULL)
	{
		free(PATH);
		free(_env);
		return (NULL);
	}
	size = sizeDoubleptr(PATHS);
	aux = malloc((size + 1) * sizeof(char *));
	if (aux == NULL)
	{
		free(PATHS);
		free(PATH);
		free(_env);
		return (NULL);
	}
	copyDoubleptr(aux, PATHS, size);
	free(PATHS);
	free(PATH);
	free(_env);
	return (aux);
}

/**
* _strcpy - prints n numbers of an array
* @dest: string to be printed
* @src: number of elements to be printed
* Return: The string copied
*/

char *_strcpy(char *dest, char *src)
{
	char *firstValue = dest;

	for (; *src != '\0'; src++)
	{
		*dest = *src;
		dest++;
	}
	*dest = '\0';
	return (firstValue);
}

/**
* divideLine - divides a line
* @line: line to be divided
* @delim: delimitator
* Return: array of arguments
*/

char **divideLine(char *line, char *delim)
{
	char **tokens = NULL;
	int i = 0, j = 0, coun_tokens = 0;

	coun_tokens = countToken(line, delim);
	if (coun_tokens == 0 || !line)
		return (NULL);
	tokens = malloc(sizeof(char *) * (coun_tokens + 1));
	if (tokens == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (i == 0 && line[i] == ' ')
		{
			while (line[i + 1] == ' ' && j == 0)
				i++;
			i++;
			tokens[j] = line + i;
			j++;
		}
		if (i == 0 && line[i] != ' ')
		{
			tokens[j] = line;
			j++;
		}
		while (line[i + 1] == *delim || line[i + 1] == ' ')
		{
			i++;
			line[i] = '\0';
			while (line[i + 1] == ' ')
			{
				i++;
				line[i] = '\0';
			}
			i++;
			tokens[j++] = line + i;
		}
		i++;
	}
	tokens[coun_tokens] = NULL;
	return (tokens);
}

/**
* stringSize - size of a string
* @str: string to be counted
* Return: size of the string
*/

int stringSize(char *str)
{
	int size = 0;

	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}

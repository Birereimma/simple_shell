#include "shell.h"

/**
 * _getenv - search string
 * @name: String name
 * @env: environment
 * Return: Pointer to the string
 */
char *_getenv(const char *name, char **env)
{
	char *ptr = NULL;
	char **list = NULL;
	int size = 0;
	int i = 0, j = 0;

	list = env;
	for (i = 0; list[i] != NULL; i++)
	{
		for (j = 0; name[j] == list[i][j]; j++)
		{
		}
		if (name[j] == '\0' && list[i][j] == '=')
		{
			/*liberar malloc*/
			size = stringSize(list[i]);
			ptr = malloc(size + 1);
			if (ptr == NULL)
			{
				return (NULL);
			}
			ptr = _strcpy(ptr, list[i]);
			return (ptr);
		}
	}
	if (name[j] == '\0' && list[i][j] == '=')
	{
		size = stringSize(list[i]);
		ptr = malloc(size + 1);
		if (ptr == NULL)
		{
			return (NULL);
		}
		_strcpy(ptr, list[i]);
	}
	return (ptr);
}

/**
 * exit_shell - exits the current shell
 * Return: void
 */
int exit_shell(void)
{
	return (-1);
}

/**
 * printEnv - prints the current environment
 * Return: always 0
 */
int printEnv(void)
{
	int i = 0, j = 0;
	char **env = __environ;

	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			write(1, &(env[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

/**
 * equalStringenv - prints the current environment
 * @str1: string 1 to be compared
 * @str2: string 2 to be compared
 * Return: always 0
 */
int equalStringenv(char *str1, char *str2)
{
	int i = 0;

	if (stringSize(str1) != stringSize(str2))
	{
		return (-1);
	}

	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

/**
 * checkBuiltin - prints the current environment
 * @str: string 1
 * @bt: string 2
 * Return: 0 if found a builtin -1 if not
 */
builtin *checkBuiltin(char *str, builtin *bt)
{
	int i = 0;

	while (bt[i].command != NULL)
	{
		if (equalStringenv(bt[i].command, str) == 0)
		{
			return (&(bt[i]));
		}
		i++;
	}
	return (NULL);
}

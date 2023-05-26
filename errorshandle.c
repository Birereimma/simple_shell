#include "shell.h"

/**
 * countDigits - Counter arrays
 * @number: value have counted
 * Return: size
 */
int countDigits(int number)
{
	int size = 0;

	if (number == 0)
		return (1);

	while (number != 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}
/**
 * transNumber - Pointer that contain the revert numbers
 * @number: to revert
 * @size: size of array
 * Return: pointer revert
 */
char *transNumber(int number, int size)
{
	char *ptr, *ptrRev;
	int i = 0, j = 0;

	ptr = malloc(size * sizeof(char) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	if (number == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	ptrRev = malloc(size * sizeof(char) + 1);
	if (ptrRev == NULL)
	{
		free(ptr);
		return (NULL);
	}
	while (i < size)
	{
		ptr[i] = (number % 10) + '0';
		number /= 10;
		i++;
	}
	ptr[i] = '\0';
	while (ptr[j] != '\0')
	{
		ptrRev[j] = ptr[i - 1];
		i--;
		j++;
	}
	ptrRev[j] = '\0';
	free(ptr);
	return (ptrRev);
}
/**
 * printErrors - Print errors
 * @arg: pointer pos1
 * @line: pointer pos2
 * @err: pointer pos3
 * @count: number of error
 * @con: conditional
 * Return: Noting
 */
void printErrors(char *arg, char *line, char *err, int count, int con)
{
		int size_coun_err = 0, size_arg = 0, size_line = 0, size_error = 0;
		char *number_trans = NULL;

		size_arg = stringSize(arg);
		size_error = stringSize(err);
		size_line = stringSize(line);
		size_coun_err = countDigits(count);
		number_trans = transNumber(count, size_coun_err);
		write(STDERR_FILENO, arg, size_arg);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, number_trans, size_coun_err);
		write(STDERR_FILENO, ": ", 2);
		if (con == 0)
		{
			write(STDERR_FILENO, line, size_line);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, err, size_error + 1);
		} else
		{
			write(STDERR_FILENO, err, size_error + 1);
			write(STDERR_FILENO, line, size_line);
			write(STDERR_FILENO, "\n", 1);
		}
		free(number_trans);
}

/**
 * printErrordir - Print errors
 * @arg: pointer pos1
 * @line: pointer pos2
 * Return: Noting
 */
void printErrordir(char *arg, char *line)
{
	int size_coun_err = 0, size_arg = 0;

	size_arg = stringSize(arg);
	size_coun_err = stringSize(line);
	write(STDERR_FILENO, arg, size_arg);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, line, size_coun_err);
	write(STDERR_FILENO, "\n", 1);
}

/**
* signintHandle - handles signs
* @sign_num: struct whit arguments builtin
* Return: Noting
*/
void signintHandle(int sign_num)
{
	signal(sign_num, SIG_IGN);
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "(&) ", 4);
	signal(SIGINT, signintHandle);
}

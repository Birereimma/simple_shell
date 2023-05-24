#include "shell.h"

/**
 * alxProgram - print on the screen
 *
 * Return: always succes
 */

int alxProgram(void)
{
	int count;
	char *message = "ALX programming program\n";
	int message_length = 30;

	for (count = 0; count < 25; count++)
	{
		write(1, message, message_length);
	}
	return (0);
}


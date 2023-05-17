#include <stdio.h>
#include <unistd.h>

/**
 * main - entry point of the program
 *
 * Return: always succes
 */

int main(void)
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


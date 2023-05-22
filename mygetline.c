#include "shell.h"

/**
 * custom_getline - read from the buffer
 * @buffer: stores input
 * @size: character read fro the buffer
 * Return: 0 or -1
 */

int custom_getline(char *buffer, size_t size)
{
	ssize_t bytesRead = 0;
	ssize_t totalBytesRead = 0;

	while(1)
	{
		bytesRead = read(STDIN_FILENO, buffer + totalBytesRead, size - totalBytesRead);
		if (bytesRead == -1)
		{
			if (errno == EINTR)
			{
				continue;
			}
			else
			{
				perror("read");
				return (-1);
			}
		}
		else if (bytesRead == 0)
		{
			break;
		}
		totalBytesRead += bytesRead;
		if ((size_t)totalBytesRead >= size - 1 || buffer[totalBytesRead - 1] == '\n')
		{
			break;
		}
	}
	buffer[totalBytesRead] = '\0';
	return (totalBytesRead);
}


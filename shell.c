#include "shell.h"

/**
 * main - entry point of the program
 *
 * Rturn: 0 on success, 1 on fail
 */

int main(void)
{
	char input[MAX_INPUT_SIZE];
	const char prompt[] = "$ ";
	pid_t child_pid;
	int status;

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

		/* fork a child process to execute the command */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			/** prepare the command line arguments arrays */
			char *args[2];
			args[0] = input;
			args[1] = NULL;

			/** execute the command using excve */
			if (execve(input, args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
			else /* parent process */
			{
				/* wait for the child process to complet */
				if (waitpid(child_pid, &status, 0) == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			}
	}
	return (0);
}






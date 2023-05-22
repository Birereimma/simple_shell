#include "shell.h"

char *findExecutable(const char *command, char *directories[], int numDirs)
{
	char *executablePath;
	size_t commandLen = strlen(command);
	size_t dirLen;
	size_t pathLen;
	size_t maxPathLen = 0;
	int i;

	for (i = 0; i < numDirs; i++)
	{
		dirLen = strlen(directories[i]);
		pathLen = dirLen + commandLen + 2; /* +2 for '/' and '\0' */
		if (pathLen > maxPathLen)
		{
			 maxPathLen = pathLen;
			 executablePath = malloc(maxPathLen);
			 if (executablePath == NULL)
			 {
				 perror("Memory allocation failed");
				 exit(EXIT_FAILURE);
			 }
		}

		/* construch the path to the executable */
		strcpy(executablePath, directories[i]);
		strcat(executablePath, "/");
		strcat(executablePath, command);

		/* check if the executable exists */
		if (access(executablePath, X_OK) == 0)
		{
			return (executablePath);
		}
	}
	free(executablePath);
	return (NULL);
}
		


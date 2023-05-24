#include "shell.h"

/**
 * tokenizeInput - tokenizes the input
 * @input: array of input
 * @tokens: numbe of tokes
 * Return: always success
 */

int tokenizeInput(const char *input, char *tokens[])
{
	char inputCopy[MAX_TOKEN_SIZE];
	int tokenCount = 0;
	char *token;

	/* Create a copy of the input string */
	strncpy(inputCopy, input, MAX_TOKEN_SIZE);
	/* Ensure the copied string is null-terminated */
	inputCopy[MAX_TOKEN_SIZE - 1] = '\0';

	token = strtok_custom(inputCopy, " \t");
	while (token != NULL && tokenCount < MAX_TOKENS)
	{
		/* Store the token in the array */
		tokens[tokenCount] = strdup(token);

		/* Get the next token */
		token = strtok_custom(NULL, " \t");
		tokenCount++;
	}
	/* Set the last element of the array to NULL */
	 tokens[tokenCount] = NULL;
	return (tokenCount);
}

/**
 * strtok_custom - tokenises a string
 * @str: input string
 * @delim: character delimitator
 * Return: alwats success
 */

char *strtok_custom(char *str, const char *delim)
{
	static char *token;
	static char *nextToken;
	char *currentToken;

	if (str != NULL)
	{
		token = str;
	}
	if (token == NULL)
	{
		return (NULL);
	}

	nextToken = strchr(token, *delim);
	if (nextToken != NULL)
	{
		*nextToken = '\0';
		nextToken++;
	}
	currentToken = token;
	token = nextToken;

	return (currentToken);
}






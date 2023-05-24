#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define MAX_DIRS 64
#define BUFFER_SIZE 1024
#define MAX_TOKENS 100
#define MAX_TOKEN_SIZE 50
#define MAX_COMMANDS 10

void parseInput(char *input, char *args[]);
void executeCommand(char *args[]);
int parsePath(const char *path, char *directories[]);
char *findExecutable(const char *command, char *directories[], int numDirs);
int parsePath(const char *path, char *directories[]);
int custom_getline(char *buffer, size_t size);
int tokenizeInput(const char *input, char *tokens[]);
char *strtok_custom(char *str, const char *delim);
void changeDirectory(char *directory);
void parseCommands(char *input, char **commands);


#endif

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 10
#define MAX_DIRS 64

void parseInput(char *input, char *args[]);
void executeCommand(char *args[]);
int parsePath(const char *path, char *directories[]);
char *findExecutable(const char *command, char *directories[], int numDirs);
int parsePath(const char *path, char *directories[]);


#endif

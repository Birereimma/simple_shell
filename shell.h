#ifndef _SHELL_H
#define _SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
 *  struct builtin - builtins struct
 *  @command: command to execute
 *  @function: function that gets executed when that command is called
 *	@type: type of process
 */

typedef struct builtin
{
	int type;
	char *command;
	int (*function)(void);
} builtin;

void startLoop(builtin *bt, char *, char **);
int executeCommand(char *command, char **args, builtin *bt);
builtin *checkBuiltin(char *str, builtin *bt);
int equalStrinenv(char *str1, char *str2);
int exit_shell(void);
int printEnv(void);
char *concatPath(char *command, char **);
void concatString(char *dest, char *src, int offset);
char **dividePath(char *str, char **);
char **copyDoubleptr(char **dest, char **src, int size);
void freeDoubleptr(char **ptr);
int sizeDoubleptr(char **ptr);
void signintHandle(int sign_num);
char *_getenv(const char *name, char **);
char *_strcpy(char *dest, char *src);
char **divideLine(char *line, char *delim);
int countToken(char *line, char *delim);
char *prompt(char *text);
int stringSize(char *str);
void freePointers(char *line, char *path, char **arguments);
char *transArguments(char **, builtin *, char *, int, char **);
char *trans_Number(int number, int size);
int countDigits(int number);
void printErrordir(char *arg, char *line);
void printErrors(char *arg, char *line, char *errorx, int count_errors, int);
#endif

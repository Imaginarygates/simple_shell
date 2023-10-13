#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#define EXIT_MISUSAGE 2
#define EXIT_BADUSAGE 2
#define EXIT_NOTFOUND 127
#define EXIT_CMDFAIL 2
#define EXIT_SUCCESS 0

extern char **environ;

/**
* struct shell_data - Structure containing commonly used shell variables.
* @name: The name of the program.
* @process: Counts the number of processes.
* @status: The exit status of the program.
* @tokens: An array of tokenized strings.
* @line: Pointer to the input string.
*
* This structure stores essential data used by the shell program.
*/
typedef struct shell_data
{
char *name;
int process;
int status;
char **tokens;
char *line;
} sh_data;

/**
* struct builtin_s - Structure for built-in function pointers.
* @builtin: The built-in function name.
* @fun_p: The function pointer.
*
* This structure associates built-in command names with their corresponding functions.
*/
typedef struct builtin_s
{
char *builtin;
int (*fun_p)(sh_data *);
} builtin_f;

/* Function Prototypes */
void interactive(sh_data *shell);
void non_interactive(sh_data *shell);
void removeNewline(char *str);
char *findExecutablePath(char *cmd);
int executeCommand(sh_data *shell);
char **tokenize(char *line);
void freeStringArray(char **ptr);
void removeComment(char *line);

/* Built-in Functions */
int handleBuiltins(sh_data *shell);
int exitShell(sh_data *shell);
int printEnvironment(sh_data *shell);
int changeDirectory(sh_data *shell);

/* String Manipulation Functions */
int compareStrings(const char *str1, const char *str2);
size_t stringLength(const char *str);
char *stringDuplicate(const char *src);
char *stringCopy(char *dest, const char *src);
char *stringConcatenate(char *dest, const char *src);

/* String to Integer Conversion */
int stringToInteger(char *s);

/* Environment Functions */
int setEnvironmentVariable(sh_data *shell);
int unsetEnvironmentVariable(sh_data *shell);
char *getEnvironmentVariable(const char *name);

/* getline.c */
void *customMemoryCopy(void *dest, const void *src, size_t n);
ssize_t refillBuffer(FILE *stream, char buf[], size_t *buf_index, ssize_t *bytes_remaining);
char *resizeLineBuffer(char *lineptr, size_t *n, ssize_t bytes_read);
ssize_t customGetLine(char **lineptr, size_t *n, FILE *stream);


#endif

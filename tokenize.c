#include "shell.h"

/**
* countTokens - Determine the number of tokens in a string.
* @line: Pointer to the line string.
*
* Return: The number of tokens found in the string.
*/
int countTokens(char *line)
{
const char *delimiters = " \t\a\r\n";
int tokenCount = 0;
char *token, *lineCopy;

lineCopy = _strdup(line);
if (lineCopy == NULL)
return -1;

token = strtok(lineCopy, delimiters);
while (token != NULL)
{
tokenCount++;
token = strtok(NULL, delimiters);
}

free(lineCopy);
return tokenCount;
}

/**
* tokenize - Split a line string into an array of string pointers.
* @line: Pointer to the line string to be tokenized.
*
* Return: An array of tokenized strings or NULL on failure.
*/
char **tokenize(char *line)
{
const char *delimiters = " \t\a\r\n";
char **tokens;
int i = 0, tokenCount;
char *lineCopy, *token;

lineCopy = _strdup(line);
if (lineCopy == NULL)
return NULL;

tokenCount = countTokens(line);
if (tokenCount == -1 || tokenCount == 0)
return NULL;

tokens = malloc(sizeof(char *) * (tokenCount + 1));
if (!tokens)
return NULL;

token = strtok(lineCopy, delimiters);
while (token != NULL)
{
tokens[i] = _strdup(token);
token = strtok(NULL, delimiters);
i++;
}
tokens[i] = NULL;
free(lineCopy);
return tokens;
}

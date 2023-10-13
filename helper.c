#include "shell.h"

/**
* removeNewline - Eliminate the newline character from a string.
* @str: Pointer to the string.
*
* This function removes the trailing newline character, if it exists, from the provided string.
*/
void removeNewline(char *str)
{
int length;

length = _strlen(str);

if (length > 0 && str[length - 1] == '\n')
str[length - 1] = '\0';
}

/**
* freeStringArray - Free memory occupied by an array of strings.
* @array: Array of strings.
*
* This function deallocates the memory used by an array of strings.
*/
void freeStringArray(char **array)
{
int i;

if (array != NULL)
{
for (i = 0; array[i]; i++)
{
free(array[i]);
}
free(array);
array = NULL;
}
}

/**
* removeComment - Remove comments from a line.
* @line: Pointer to the line string.
*
* This function removes comments from a line by ignoring everything after a '#' character.
*/
void removeComment(char *line)
{
int i = 0;

if (*line == '#')
	*line = '\0';

while (line[i] != '\0')
{
if (line[i] == '#' && line[i - 1] == ' ')
break;
i++;
}
line[i] = '\0';
}

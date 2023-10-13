#include "shell.h"

/**
* findExecutablePath - Find the full path to an executable.
* @cmd: The executable command.
*
* This function attempts to find the full pathname for the given executable command.
* It searches through the directories listed in the PATH environment variable and returns
* the first matching pathname found.
*
* Return: The full pathname of the executable if found, or NULL if not found.
*/
char *findExecutablePath(char *cmd)
{
char *path, *pathCopy, *dir, *temp;
struct stat st;

if (stat(cmd, &st) == 0)
return _strdup(cmd);

pathCopy = getenv("PATH");
if (pathCopy == NULL)
return NULL;

path = _strdup(pathCopy);

temp = strtok(path, ":");

while (temp != NULL)
{
dir = malloc(_strlen(temp) + _strlen(cmd) + 2);

dir = _strcpy(dir, temp);
dir = _strcat(dir, "/");
dir = _strcat(dir, cmd);

if (stat(dir, &st) == 0)
{
free(path);
return dir;
}
free(dir);

temp = strtok(NULL, ":");
}
free(path);

return NULL;
}

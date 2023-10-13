#include "shell.h"

/**
* interactive - Run the shell in interactive mode.
* @shell: A pointer to the shell data structure.
*
* This function runs the shell in interactive mode, continuously prompting for user input,
* processing the input, and executing commands as entered by the user.
*/
void interactive(sh_data *shell)
{
char *path;
size_t line_buffer_size = 0;
ssize_t line_length;
int builtins_result;

while (1)
{
shell->process++;
write(1, "$ ", 2);
line_length = _getline(&shell->line, &line_buffer_size, stdin);

if (line_length == -1)
{
perror("Error reading input");
exit(EXIT_FAILURE);
}

removeNewline(shell->line);
removeComment(shell->line);
shell->tokens = tokenize(shell->line);

if (shell->tokens == NULL)
continue;

builtins_result = executeBuiltins(shell);

if (builtins_result == 1)
continue;

path = findExecutablePath(*shell->tokens);

if (path != NULL)
{
if (_strcmp(path, *shell->tokens) != 0)
{
free(*shell->tokens);
*shell->tokens = _strdup(path);
free(path);
}

shell->status = executeCommand(shell);
}
else
{
dprintf(STDERR_FILENO, "%s: %d: %s: command not found\n", shell->name, shell->process, *shell->tokens);
shell->status = EX_NOTFOUND;
}

freeStringArray(shell->tokens);
}

free(shell->line);
}

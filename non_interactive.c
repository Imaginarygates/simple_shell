#include "shell.h"

/**
* nonInteractive - Handles the shell when it's not in interactive mode.
* @shell: Pointer to the shell data structure.
*
* This function manages the shell when it's running in non-interactive mode,
* processing input from a non-terminal source.
*/
void nonInteractive(sh_data *shell)
{
char *path;
size_t line_buffer_size = 0;
int builtins_result;

while (_getline(&shell->line, &line_buffer_size, stdin) != -1)
{
shell->process++;

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
*shell->tokens = strdup(path);
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

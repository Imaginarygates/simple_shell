#include "shell.h"

/**
* executeCommand - Execute a command by forking a child process and calling execve.
* @shell: A pointer to the shell data structure.
*
* This function forks a child process and attempts to execute a command using execve.
* The function returns the exit status of the child process or an error status if the
* fork or execve operation fails.
*
* Returns: The exit status of the child process or an error status.
*/

int executeCommand(sh_data *shell)
{
pid_t pid;
int status;
char **env = environ;

// Fork a new process
pid = fork();

if (pid == -1)
{
perror("Fork operation failed");
free_array(shell->tokens);
free(shell->line);
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
// Child process
if (execve(shell->tokens[0], shell->tokens, env) < 0)
{
perror("Execution of command failed");
free_array(shell->tokens);
free(shell->line);
exit(EX_BADUSAGE);
}
}
else
{
// Parent process
wait(&status);

// Check if the child process was terminated by a signal or exited normally
if (WIFSIGNALED(status))
status = WTERMSIG(status);
else if (WIFEXITED(status))
status = WEXITSTATUS(status);

return status;
}
}

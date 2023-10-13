#include "shell.h"

/**
* main - The primary entry point of the shell program.
* @ac: The number of command-line arguments.
* @av: An array of pointers to the command-line arguments.
*
* This is the main function responsible for initializing the shell data structure,
* determining whether the shell is running interactively or non-interactively, and
* managing the shell's execution accordingly.
*
* Return: The status code of the shell process.
*/
int main(int ac, char **av)
{
sh_data shell;
(void)ac; // Avoid unused parameter warning

shell.process = 0;
shell.status = 0;
shell.name = *av;
shell.line = NULL;

if (isatty(STDIN_FILENO))
interactive(&shell);
else
nonInteractive(&shell);

return shell.status;
}

#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
* is_interactive - Check if the shell is running in interactive mode.
*
* Return: 1 if the shell is in interactive mode, 0 otherwise.
*/
int is_interactive(void)
{
return (isatty(STDIN_FILENO));
}

/**
* shell_execute - Execute a shell command.
*
* This function checks if the provided command is a built-in shell command,
* and if so, it executes the corresponding built-in function. If the command
* is not a built-in, it launches an external program to execute the command.
*
* @args: The command and its arguments as an array of strings.
* Return: 1 to continue shell execution, or 0 to exit the shell.
*/
int shell_execute(char **args)
{
int i;
int status;
char *built_in_string[] =

{
"cd",
"help",
"exit",
"env",
NULL};
if (args[0] == NULL)
{
return (1);
}

for (i = 0; i < shell_builtins(); i++)
{
if (strcmp(args[0], built_in_string[i]) == 0)
{
return ((*built_in_function[i])(args));
}
}

/* Launch the external program using fork_cmd */
status = fork_cmd(args[0], args);

return (status);
}

#include "shell.h"

/**
* shell_cd - Change the current working directory to the one specified.
*
* @args: An array of strings where args[0] is "cd" and args[1] is destination
* Return: Always returns 1 to continue shell execution.
*/
int shell_cd(char **args)
{

if (args[1] == NULL)
{
char error_message[] = "shell: expected argument to cd\n";
write(STDERR_FILENO, error_message, strlen(error_message));
}

else
{
if (chdir(args[1]) != 0)
{
perror("shell");
}
}
return (1);
}

/**
* shell_builtins - Get the number of built-in shell commands.
*
* Return: The number of built-in shell commands.
*/
int shell_builtins(void)
{
int count = 0;
char *built_in_string[] =

{
"cd",
"help",
"exit",
"env",
NULL};

/* Iterate through the array until the NULL sentinel is encountered */
while (built_in_string[count] != NULL)
{
count++;
}

return (count);
}

/**
* shell_exit - Exit the shell program.
*
* @args: Not used for this command.
* Return: Always returns 0 to exit the shell.
*/
int shell_exit(char **args)
{
if (args[1] != NULL)
{
/* Try to convert the argument to an integer */
char *endptr;
int status = (int)strtol(args[1], &endptr, 10);
if (*endptr == '\0' && status >= 0)
{
exit(status);
}
else
{
fprintf(stderr, "Invalid exit status: %s\n", args[1]);
return (1);
}
}
else
{
/* If no argument is provided, exit with the default status 0 */
exit(0);
}
}

/**
* shell_env - Custom 'env' command to print the current environment variables.
*
* @args: The command and its arguments.
* Return: 1 to continue execution.
*/
int shell_env(char **args)
{
char **env = environ;
/* Ensure that the 'env' command has no additional arguments. */
if (args[1] != NULL)
{
_puts("shell: env: too many arguments\n");
return (1);
}

/* Print the current environment variables. */
else
{
while (*env)
{
_puts(*env);
_putchar('\n');
env++;
}
}

return (1);
}

int (*built_in_function[])(char **) = {
&shell_cd,
&shell_help,
&shell_exit,
&shell_env,
};

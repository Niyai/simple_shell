#include "shell.h"

/**
* fork_cmd - Execute a command if it contains '/', or search in PATH.
*
* @cmd: The command to execute.
* @argv: An array of strings containing the command and its arguments.
* Return: 1 to continue shell execution, or 0 in case of an error.
*/
int fork_cmd(const char *cmd, char *const argv[])
{
if (strchr(cmd, '/') != NULL)
{
return (fork_execute_directly(cmd, argv));
}
else
{
return (fork_search_in_path(cmd, argv));
}
}

/**
* fork_execute_directly - Execute a command that contains a '/' directly.
*
* @cmd: The command to execute.
* @argv: An array of strings containing the command and its arguments.
* Return: 1 to continue shell execution, or 0 in case of an error.
*/
int fork_execute_directly(const char *cmd, char *const argv[])
{
pid_t child_pid;
int status;

child_pid = fork();
if (child_pid == -1)
{
perror("Fork error");
return (0);
}
if (child_pid == 0)
{
if (execve(cmd, argv, environ) == -1)
{
perror("Exec error");
exit(1);
}
}
else
{
do {
if (waitpid(child_pid, &status, WUNTRACED) == -1)
{
perror("Waitpid error");
break;
}
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
return (1);
}
return (1);
}

/**
* fork_search_in_path - Execute a command by searching in PATH directories.
*
* @cmd: The command to execute.
* @argv: An array of strings containing the command and its arguments.
* Return: 1 to continue shell execution, or 0 in case of an error.
*/
int fork_search_in_path(const char *cmd, char *const argv[])
{
char *path_env = getenv("PATH");
char *path_copy = strdup(path_env);
char *token = custom_strtok(path_copy, ":");
int status = 0;

if (path_env == NULL)
{
perror("PATH environment variable not set");
return (0);
}

while (token != NULL)
{
char full_path[MAX_PATH_LENGTH];
snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", token, cmd);

if (access(full_path, X_OK) == 0)
{
status = fork_execute_directly(full_path, argv);
if (status == 1)
{
free(path_copy);
return (1);
}
}
token = custom_strtok(NULL, ":");
}

free(path_copy);
perror("Command not found");
return (1);
}

#include "shell.h"

/**
* shell_read_line - Read a line of input from the user.
*
*
* void: The user's input line.
* Return: line.
*/
char *shell_read_line(void)
{
char *line = NULL;
size_t bufsize = 0;

if (custom_getline(&line, &bufsize, stdin) == -1)
{
if (feof(stdin))
{
exit(EXIT_SUCCESS);
}
else
{
perror("shell: getline");
exit(EXIT_FAILURE);
}
}

return (line);
}

/**
* shell_split_line - Split a line into individual tokens.
*
* @line: The input line.
* Return: An array of tokens.
*/
char **shell_split_line(char *line)
{
int bufsize = shell_TOK_BUFSIZE;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens)
{
perror("shell");
exit(EXIT_FAILURE);
}

token = custom_strtok(line, shell_TOK_DELIM);

while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += shell_TOK_BUFSIZE;
tokens = realloc(tokens, bufsize *sizeof(char *));
if (!tokens)
{
perror("shell");
exit(EXIT_FAILURE);
}
}

token = custom_strtok(NULL, shell_TOK_DELIM);
}

tokens[position] = NULL;
return (tokens);
}

#include "shell.h"

/**
* main - function for the custom shell program.
*
* @argc: Number of command-line arguments.
* @argv: Array of strings representing command-line arguments.
* Return: An integer indicating the exit status of the shell.
*/
int main(int argc, char **argv)
{
if (argc > 1 && is_interactive())
{
fprintf(stderr, "Cannot read cmd from terminal in noninteractive mode.\n");
return (EXIT_FAILURE);
}

if (argc > 1)
{
/*  Non-interactive mode: Read commands from a file or a pipe */
process_input(stdin);
}
else
{
/*  Interactive mode: Wait for user input */
shell_loop();
(void)argv;
}

return (EXIT_SUCCESS);
}

/**
* process_input - Process input from file or input stream executing commands
*
* @input: The file or input stream to read commands from.
* Return: void
*/
void process_input(FILE *input)
{
char *line = NULL;
size_t len = 0;
char **args = NULL;
int status;
char *token = custom_strtok(line, "|");

while (custom_getline(&line, &len, input) != -1)
{
/* Remove trailing newline character, if any */
if (line[strlen(line) - 1] == '\n')
{
line[strlen(line) - 1] = '\0';
}

/* Split the line into commands based on pipe ('|') */
while (token != NULL)
{
/* Split each command into arguments */
args = shell_split_line(token);
status = shell_execute(args);

/* Free allocated memory for arguments */
free(args);

/* Get the next part of the pipe, if any */
token = custom_strtok(NULL, "|");
}

if (!is_interactive() && status == 0)
{
break; /* Exit the shell if the executed cmd returns 0 in non-interactive */
}

free(line); /* Reset the line and args for the next iteration */
line = NULL;
args = NULL;
}
free(line);
}

/**
* shell_loop - Start the interactive shell loop, accepting user commands.
* Return: void
*/
void shell_loop(void)
{
char *line;
char **args;
int status;

do {
if (is_interactive())
{
write(STDOUT_FILENO, "> ", 2);
}
line = shell_read_line();
args = shell_split_line(line);
status = shell_execute(args);
free(line);
free(args);
} while (is_interactive() && status);
}

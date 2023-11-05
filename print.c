#include "shell.h"

/**
* _putchar - Write a character to the standard output.
*
* @c: The character to be written.
* Return: The character written as an unsigned char converted to an int.
*/
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _puts - Print a string to the standard output.
*
* @str: The string to be printed.
* Return: void
*/
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
* shell_help - Display information about available shell commands.
*
* @args: Not used for this command.
* Return: Always returns 1 to continue shell execution.
*/
int shell_help(char **args)
{
char *built_in_string[] =

{

"cd",

"help",

"exit",

"env"

};

int i;
char message[] = "This is a simple C shell built by Niyi Akinwale\n"
"Type program names and arguments, and hit enter.\n"
"The following are built-in commands:\n";
char info[] = "Use the man command for information on other programs.\n";
(void)args;

write(STDOUT_FILENO, message, strlen(message));

for (i = 0; i < shell_builtins(); i++)
{
write(STDOUT_FILENO, " ", 1);
write(STDOUT_FILENO, built_in_string[i], strlen(built_in_string[i]));
write(STDOUT_FILENO, "\n", 1);
}

write(STDOUT_FILENO, info, strlen(info));

return (1);
}

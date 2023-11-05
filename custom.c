#include "shell.h"

/**
* custom_strtok - Split a string into tokens using a given set of delimiters.
*
* This function splits a string into tokens using the provided delimiters. It
* maintains state across calls, making it suitable for parsing a string in
* multiple steps.
*
* @str: The string to split (pass NULL to continue from the last string).
* @delim: The set of delimiter characters to use for tokenization.
* Return: A pointer to the next token in the string.
*/
char *custom_strtok(char *str, const char *delim)
{
static char *saved;
char *token;

if (str != NULL)
{
saved = str;
}

if (saved == NULL)
{
return (NULL);
}
while (*saved && strchr(delim, *saved))
{
saved++;
}

if (*saved == '\0')
{
return (NULL);
}

token = saved;

while (*saved && !strchr(delim, *saved))
{
saved++;
}

if (*saved)
{
*saved = '\0';
saved++;
}
else
{
saved = NULL;
}
return (token);
}

/**
* custom_getline - Read a line of input from the user.
*
* This function reads a line of input from the standard input (stdin) and
* returns a dynamically allocated string containing the line.
*
* @lineptr: A pointer to a pointer to the string containing the input line.
* @n: A pointer to the size of the allocated buffer.
* @stream: The input stream (e.g., stdin).
*
* Return: The number of characters read, or -1 on error or end of file (EOF).
*/
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
if (!lineptr || !n)
{
errno = EINVAL;
return (-1);
}

if (!*lineptr || !*n)
{
*n = INIT_BUFFER_SIZE;
*lineptr = (char *)malloc(*n);
if (!*lineptr)
{
return (-1);
}
}

return (custom_getline_helper(lineptr, n, stream));
}
/**
 * custom_getline_helper - Read a line of input from the user.
 *
 * This function reads a line of input from the specified input stream and
 * stores it in the dynamically allocated buffer pointed to by 'lineptr'.
 * It is designed to be used as a help function for 'custom_getline'.
 *
 * @lineptr: A pointer to a pointer to the string containing the input line.
 * @n: A pointer to the size of the allocated buffer.
 * @stream: The input stream (e.g., stdin).
 *
 * Return: The number of characters read, or -1 on error or end of file (EOF).
 */
ssize_t custom_getline_helper(char **lineptr, size_t *n, FILE *stream)
{
char *line = *lineptr;
size_t size = *n;
size_t pos = 0;
int c;
char *new_line;
while (1)
{c = fgetc(stream);
if (c == EOF)
{
if (ferror(stream))
{
return (-1);
}
break;
}
line[pos++] = (char)c;
if (pos >= size - 1)
{size *= 2;
new_line = (char *)realloc(*lineptr, size);
if (!new_line)
{
free(*lineptr);
return (-1);
}
*lineptr = new_line;
line = *lineptr;
}
if (c == '\n')
{
line[pos] = '\0';
*n = size;
return (pos);
}
}
if (pos > 0)
{line[pos] = '\0';
*n = size;
return (pos);
}
return (-1);
}

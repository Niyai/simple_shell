#ifndef shell_SHELL_H
#define shell_SHELL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>

#define shell_TOK_BUFSIZE 64
#define shell_TOK_DELIM " \t\r\n\a"
#define WRITE_BUF_SIZE 1024 /* Define the buffer size as needed */
#define BUF_FLUSH '\0'      /* Define a character to flush the buffer. */
#define MAX_PATH_LENGTH 4096
#define MAX_LINE_SIZE 1024
#define INIT_BUFFER_SIZE 128

extern char *built_in_string[];
extern int (*built_in_function[])(char **);

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_builtins(void);
int _putchar(char c);
void _puts(char *str);
int shell_env(char **args);
void process_input(FILE *input);
extern char **environ;

int shell_launch(char **args);
void shell_loop(void);
int shell_execute(char **args);
char *shell_read_line(void);
char **shell_split_line(char *line);
int is_interactive(void);
int fork_cmd(const char *cmd, char *const argv[]);
int fork_execute_directly(const char *cmd, char *const argv[]);
int fork_search_in_path(const char *cmd, char *const argv[]);
char *custom_strtok(char *str, const char *delim);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
ssize_t custom_getline_helper(char **lineptr, size_t *n, FILE *stream);
#endif

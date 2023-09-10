#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 1024 


/** Function prototypes*/

void display_prompt(void);
char *read_command(void);
void execute_command(char *command);
char **parse_command_with_args(char *command);
char *search_command_in_path(char *command);
void shell_exit(int status);
void shell_env(void);
ssize_t my_getline(char **lineptr, size_t *n);
char **split_line(char *line);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int shell_cd(char **args);
int execute_separated_commands(char *command);
int execute_logical_operators(char *command);
int handle_alias(char **args);
char *replace_variables(char *line);
/**char *remove_comments(char *line);*/
int execute_commands_from_file(const char *filename);

#endif

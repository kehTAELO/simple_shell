#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

/* Function prototypes */
int handle_builtins(char **args);
int execute_external(char **args);
int _myexit(char **args);
int _mycd(char **args);
int _myhelp(char **args);

/**
 * main(void) - The main function initializes the shell
 * @return An integer representing the exit status of the program
 */


int main(void)
{
int exitcheck = 0;
char input[MAX_INPUT_LENGTH];
while (1)
{
printf("advanced_shell> ");
if (!fgets(input, sizeof(input), stdin))
{
printf("\nExiting advanced_shell.\n");
break;
}
input[strcspn(input, "\n")] = '\0';
char *args[MAX_INPUT_LENGTH];
int num_args = 0;
char *token = strtok(input, " ");
while (token != NULL)
{
args[num_args++] = token;
token = strtok(NULL, " ");
}
args[num_args] = NULL;
if (num_args > 0)
{
int status = handle_builtins(args);
if (status == -2)
{
printf("Exiting advanced_shell.\n");
break;
}
else if (status == 1)
{
printf("Error occurred.\n");
}
else if (status == 0)
{
printf("Built-in command executed.\n");
}
else
{
int result = execute_external(args);
if (result != 0)
{
printf("External command failed.\n");
}
}
}
}
return (exitcheck);
}

/**
 * @handle_builtins - Handles the execution of built-in shell commands.
 *
 * This function checks if the given command is a built-in shell command
 * @param args An array of strings representing the command and its arguments.
 * @return An integer representing the exit status
 */

int handle_builtins(char **args)
{
if (strcmp(args[0], "exit") == 0)
{
return (_myexit(args));
}
else if (strcmp(args[0], "cd") == 0)
{
return (_mycd(args));
}
else if (strcmp(args[0], "help") == 0)
{
return (_myhelp(args));
}
return (-1);
}

/**
 * _myexit Implements the built-in 'exit' command
 * This function handles the 'exit' command
 * @param args An array of strings representing the command and its arguments.
 * @return An integer representing the exit status.
 */

int _myexit(char **args)
{
if (args[1])
{
int exitcheck = atoi(args[1]);
if (exitcheck == 0 && strcmp(args[1], "0") != 0)
{
printf("Illegal number: %s\n", args[1]);
return (1);
}
return (exitcheck);
}
return (0);
}

/**
 * _myhelp - Handles the "help" built-in shell command.
 * @param args An array of strings representing the command and its arguments.
 * @return An integer representing the result of the "help" command execution
 */

int _mycd(char **args)
{
if (args[1] == NULL)
{
fprintf(stderr, "cd: missing argument\n");
return (1);
}
else
{
if (chdir(args[1]) != 0)
{
perror("cd");
return (1);
}
}
return (0);
}

/**
 * _myhelp - Implements the built-in 'help' command.
 * @param args An array of strings representing the command and its arguments.
 * @return An integer
 */

int _myhelp(char **args)
{
printf("This is a simple shell program.\n");
printf("Supported built-in commands: exit, cd, help\n");
printf("You can also run external commands.\n");
return (0);
}

/**
 * execute_external - This fuction executes external commands
 * @param args An array of strings representing commands
 * @return An integer
 */

int execute_external(char **args)
{
pid_t pid;
int status;

pid = fork();

if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("shell");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("shell");
return (1);
}
else
{
do

{
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (0);
}

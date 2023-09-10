#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

/**
 * handle_builtins - Handle built-in commands
 * @args: The command line arguments
 *
 * Return: -2 if the command is "exit", 1 if the command is a built-in command,
 * 0 if the command is not a built-in command
 */

int handle_builtins(char **args)
{
int status = handle_builtins(args);
return 0;
}

/**
 * execute_external - Execute an external command
 * @args: The command line arguments
 * @env: The environment variables
 */

void execute_external(char **args, char **env);

int _myenv(char **args, char **env);
char *_getenv(const char *name, char **env);

/**
 * main - Simple shell program that can handle the PATH and execute commands
 *
 * Return: Always 0
 */

int main()
{
char input[MAX_INPUT_LENGTH];

char **env = (char **)malloc(sizeof(char *) * MAX_INPUT_LENGTH);
if (env == NULL)
{
perror("malloc");
return 1;
}
/** if (populate_env_list(env) != 0) {
fprintf(stderr, "Error populating environment variables.\n");
return 1;
}*/


while (1)
{
printf("simple_shell> ");

if (!fgets(input, sizeof(input), stdin))
{
printf("\nExiting simple_shell.\n");
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
printf("Exiting simple_shell.\n");
break;
} else if (status == 1)
{
}
else if (status == 0) 
{
}
else
{
execute_external(args, env);
}
}
}
for (int i = 0; env[i] != NULL; i++)
{
free(env[i]);
}
free(env);

return (0);
}

/**
 * execute_external - Execute an external command
 * @args: The command line arguments
 * @env: The environment variables
 */

void execute_external(char **args, char **env)
{
char *path = _getenv("PATH", env);
char *token = strtok(path, ":");

while (token != NULL)
{
char path_to_exec[MAX_INPUT_LENGTH];
snprintf(path_to_exec, sizeof(path_to_exec), "%s/%s", token, args[0]);

if (access(path_to_exec, X_OK) == 0)
{
pid_t pid = fork();

if (pid == -1)
{
perror("fork");
}
else if (pid == 0) {
execv(path_to_exec, args);
perror("execv");
exit(EXIT_FAILURE);
}
else
{
int status;
waitpid(pid, &status, 0);
}
break;
}
token = strtok(NULL, ":");
}
}

/**
 * _myenv - Print the environment variables
 * @args: The command line arguments (unused)
 * @env: The environment variables
 *
 * Return: Always 0
 */

int _myenv(char **args, char **env) {
	if (env == NULL) {
	printf("Environment variable list is empty.\n");
	return 1;
	}
	for (int i = 0; env[i] != NULL; i++) {
	printf("%s\n", env[i]);
	}
	return 0;
}


/**
 * _getenv - Get the value of an environment variable
 * @name: The name of the environment variable
 * @env: The environment variables
 *
 * Return: The value of the environment variable, or NULL if not found
 */

char *_getenv(const char *name, char **env)
{
	if (env == NULL || name == NULL) {
		return NULL;
	}
	for (int i = 0; env[i] != NULL; i++) {
	if (strncmp(env[i], name, strlen(name)) == 0) {
	char *value = strchr(env[i], '=');
            if (value != NULL) {
	return value + 1;
	    }
	}
	}
	return NULL;
}


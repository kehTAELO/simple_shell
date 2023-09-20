#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

/* Function prototypes */
int handle_builtins(char **args);
void execute_external(char **args, char **env);
int _myenv(char **env);
char *_getenv(const char *name, char **env);

/* this is a new fuction called in the main function*/
void my_function(void);

/**
 * @Print environment variables.
 *
 * This function prints the environment variables to the standard output.
 *
 * @param env An array of strings representing environment variables.
 * @return 0 on success, or an error code on failure.
 */

int _myenv(char **env) {
    int i;

    /* Print each environment variable */
    for (i = 0; env[i] != NULL; i++) {
        printf("%s\n", env[i]);
    }

    return 0;
}

#define INCLUDE_MAIN
#ifdef INCLUDE_MAIN

/**
 * @Main function for running the environ command.
 *
 * This function serves as the entry point for executing the "environ" command,
 * which prints environment variables.
 */

int run_environ() {
    /* i will Declare all my variables at the beginning of the function to solve the error */
    char input[MAX_INPUT_LENGTH];
    int i;
    char *args[MAX_INPUT_LENGTH];
    int num_args = 0;
    char *token;
    char **env = (char **)malloc(sizeof(char *) * MAX_INPUT_LENGTH);

    /* Call my_function after all declarations */
    my_function();

    if (env == NULL) {
        perror("malloc");
        return 1;
    }

    while (1) {
        printf("simple_shell> ");

        if (!fgets(input, sizeof(input), stdin)) {
            printf("\nExiting simple_shell.\n");
            break;
        }
        input[strcspn(input, "\n")] = '\0';

        token = strtok(input, " ");

        while (token != NULL) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;

        if (num_args > 0) {
            int status = handle_builtins(args);
            if (status == -2) {
                printf("Exiting simple_shell.\n");
                break;
            }
            else if (status == 1) {
                _myenv(env);
            }
            else {
                execute_external(args, env);
            }
        }
    }

    for (i = 0; env[i] != NULL; i++) { /* Move 'i' declaration here */
        free(env[i]);
    }
    free(env);

    return 0;
}

#endif


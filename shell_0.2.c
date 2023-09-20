#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 *main - main code entry
 *@argc: argument count
 *@argv: argument variable
 *Return: 0 (always)
 */

int start_shell(int argc, char **argv)
{
    char *prompt = "(Shell) $";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t n_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;

    (void)argc;

    while (1)
    {
        printf("%s", prompt);
        n_read = getline(&lineptr, &n, stdin);

        if (n_read == -1)
        {
            printf("exiting shell\n");
            return (-1);
        }

        lineptr_copy = malloc(sizeof(char) * n_read);
        if (lineptr_copy == NULL)
        {
            perror("memory allocation error");
            return (-1);
        }

        strcpy(lineptr_copy, lineptr);

        if (n_read == -1)
        {
            printf("Exiting shell\n");
            return (-1);
        }

        else
        {
            token = strtok(lineptr, delim);

            while (token != NULL)
            {
                num_tokens++;
                token = strtok(NULL, delim);
            }
            num_tokens++;

            argv = malloc(sizeof(char *) * num_tokens);

            token = strtok(lineptr_copy, delim);

            for (i = 0; token != NULL; i++)
            {
                argv[i] = malloc(sizeof(char) * strlen(token));
                strcpy(argv[i], token);

                token = strtok(NULL, delim);
            }
            argv[i] = NULL;

            printf("%s\n", lineptr);

            free(argv);
            free(lineptr);
            free(lineptr_copy);
        }
        return (0);
    }
}

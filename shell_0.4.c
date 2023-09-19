#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * main - Main code entry
 * @argc: Argument count
 * @argv: Argument variables
 * Return: 0 (always)
 */

int main(int argc, char *argv[])
{
    char *prompt = "(Shell) $";
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t n_read;

    (void)argc; (void)argv;

    while (1)
    {
        printf("%s", prompt);
        n_read = getline(&lineptr, &n, stdin);

        if (n_read == -1)
        {
            printf("Exiting shell\n");
            free(lineptr);
            exit(0);
        }

        printf("%s\n", lineptr);
    }

    return (0);
}


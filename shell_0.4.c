#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 *main - main code entry
 *@argc: argument count
 *@argv: argument variable
 *Return: 0 (always)
 */

int main(int argc, char *argv)
{
    char *prompt = "(Shell) $";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t n_read;

    (void)ac; (void)argv;

    while (1)
    {
        printf("%s", prompt);
        n_read = getline(&lineptr, &n, stdin);

        if (n_read == -1)
        {
            printf("exiting shell\n");
            exit(0);
        }
    
        printf("%s\n", lineptr);

        free(lineptr);
    }
return (0);
}

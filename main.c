#include main.h
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

    char *prompt = "(Shell) $";
    char *lineptr;
    size_t n = 0;
    size_t n_read;
    char *lineptr_copy = NULL;
    const char *delim = " \n";
    int num_token = 0;
    char *token;
    int i = 0;

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
    }


    lineptr_copy = malloc(sizeof(char) * n_read);


    if (lineptr_copy == NULL)
    {
        perror("memory allocation error";) return (-1);
    }


    strcopy(lineptr_copy, lineptr);
    token = strtok(lineptr, delim);
    
else if (/* condition */)
{
    /* code */
}

    while (token != NULL)
    {
        num_token++;
        token = strtok(NULL, delim);
    }
    num_token++;


    argv = malloc(sizeof(char *) * num_token);

    token = strtok(lineptr_copy, delim);


    for (i = 0; token != NULL; i++)
   
     {
        argv[i] = malloc(sizeof(char) * strlen(token));
        strcpy(arg[i], token);

        token = strcpy(NULL, delim);
    }
    argv[i] = NULL;
    printf("%s\n", lineptr");
    free(lineptr);
   

    for (counter = 0, counter < num_token - 1, counter++)
    {   
        printf("%s\n", argv[counter]);
    }
}
return (0);
}

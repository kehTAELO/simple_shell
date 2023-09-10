#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *prompt = "(Shell) $";
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t n_read;
    char *lineptr_copy = NULL;
    const char *delim = " \n";
    int num_token = 0;
    char *token;
    int i = 0;
    
    while (1)
    {
        printf("%s", prompt);
        n_read = getline(&lineptr, &n, stdin);
        
        if (n_read == -1)
        {
            printf("exiting shell\n");
            free(lineptr);
            free(lineptr_copy);
            return -1;
        }
        
        lineptr_copy = malloc(sizeof(char) * n_read);
        
        if (lineptr_copy == NULL)
        {
            perror("memory allocation error");
            free(lineptr);
            return -1;
        }
        
        strcpy(lineptr_copy, lineptr);
        token = strtok(lineptr, delim);
        
        while (token != NULL)
        {
            num_token++;
            token = strtok(NULL, delim);
        }
        
        num_token++;
        
        char **argv = malloc(sizeof(char *) * num_token);
        
        token = strtok(lineptr_copy, delim);
        
        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(argv[i], token);
            token = strtok(NULL, delim);
        }
        argv[i] = NULL;
        printf("%s\n", lineptr);
        free(lineptr);
        
        for (int counter = 0; counter < num_token - 1; counter++)
        {   
            printf("%s\n", argv[counter]);
            free(argv[counter]);
        }
        free(argv);
    }
    
    return 0;
}


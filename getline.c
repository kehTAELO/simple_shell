#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define READ_BUF_SIZE 1024

#define BUF_FLUSH 0
#define CMD_NORM 0

typedef struct
{
    char *cmd_buf;
    int linecount_flag;
    int cmd_buf_type;
    int histcount;
    int readfd;
} info_t;

void split_input(char *input, char *args[], int *num_args);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int is_chain(char *buf, size_t *j);
void check_chain(char *buf, size_t *j, size_t i, size_t len);
void remove_comments(char *buf);
void sigintHandler(int sig_num);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);

/**
 * split_input - Splits an input string into an array of arguments
 * @input: The input string to be split
 * @args: An array to store the split arguments
 * @num_args: A pointer to an integer to store the number of arguments
 *
 * Description:
 * This function tokenizes  input string using spaces and tabs as delimiters.
 * It stores the split arguments in the 'args' array and updates 'num_args'
 * with the total number of arguments.
 */

void split_input(char *input, char *args[], int *num_args)
{
    char *token;
    const char delimiters[] = " \t";
    int i = 0;
    *num_args = 0;
    token = strtok(input, delimiters);
    while (token != NULL)
    {
        args[i] = (char *)malloc(strlen(token) + 1);
        strcpy(args[i], token);
        (*num_args)++;
        i++;
        token = strtok(NULL, delimiters);
    }
    args[i] = NULL;
}

/**
 * read_buf - Reads data from a file descriptor into a buffer
 * @info: A pointer to the info_t struct containing relevant information
 * @buf: The buffer to store the read data
 * @i: A pointer to the size of the data read
 * Description:
 * This function reads data from the file descriptor specified in the 'info' struct
 * into the 'buf' buffer. It updates the 'i' parameter with the size of the data read.
 *
 * Return:
 * On success, the number of bytes read is returned. On failure, -1 is returned.
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;
    if (*i)
    {
        return (0);
    }
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
    {
        *i = r;
    }
    return (r);
}

/**
 * is_chain - Checks if there is a command chain delimiter in the input buffer
 * @info: A pointer to the info_t struct containing relevant information
 * @buf: The input buffer to check
 * @j: A pointer to the current position in the buffer
 *
 * Description:
 * This function examines the 'buf' buffer starting from the current position
 * indicated by 'j' and checks if there is a command chain delimiter (';').
 *
 * Return:
 * - If a command chain delimiter is found, 1 is returned, and 'j' is updated to
 *   point to the position immediately after the delimiter.
 * - If no delimiter is found, 0 is returned, and 'j' remains unchanged.
 */



int is_chain(char *buf, size_t *j)
{
    char *ptr = buf + *j;
    while (*ptr == ' ' || *ptr == '\t')
    {
        ptr++;
    }
    if (*ptr == ';')
    {
        *ptr = '\0';
        *j = (size_t)(ptr - buf);
        return (1);
    }
    return (0);
}

/**
 * check_chain - Checks for command chain delimiter in the input buffer
 * @info: A pointer to the info_t struct containing relevant information
 * @buf: The input buffer to check
 * @j: A pointer to the current position in the buffer
 * @i: The starting position for checking
 * @len: The length of the buffer
 * Description:
 * This function examines  'buf' buffer starting from position 'i'.
 *
 * Return:
 * This function wont return a value explicitly, but it updates 'i'
 * 'len' based on whether a delimiter is found or not.
 */

void check_chain(char *buf, size_t *j, size_t i, size_t len)
{
    char *ptr = buf + i;
    while (i < len && (*ptr == ' ' || *ptr == '\t'))
    {
        ptr++;
        i++;
    }
    if (i < len && *ptr == ';')
    {
        *j = i;
        ptr++;
        i++;
        while (i < len && (*ptr == ' ' || *ptr == '\t'))
        {
            ptr++;
            i++;
        }
    }
}

/**
 * strip_comments - Remove comments from a string
 * @buf: The input string from which comments should be removed
 * Description:
 * This function takes a string 'buf' and removes any comments starting with
 * the '#' character.
 * Return:
 * This function does not return a value.
 */


void strip_comments(char *buf)
{
    char *comment_start = strchr(buf, '#');
    if (comment_start != NULL)
    {
        *comment_start = '\0';
    }
}

/**
 * sigintHandler - Signal handler for SIGINT
 * @sig_num: The signal number
 *
 * Description:
 * This function is a signal handler for the SIGINT signal, which is typically.
 * Return:
 * This function doesn't return a value as it's a signal handler.
 */

void sigintHandler(int sig_num)
{
    (void)sig_num;
    puts("\nShell> ");
    putchar(BUF_FLUSH);
}


/**
 * input_buf - Read and buffer input from standard input
 * @info: A pointer to the info_t struct containing program information
 * @buf: A pointer to the buffer for storing the input
 * @len: A pointer to the length of the buffer
 *
 * Description:
 * This function reads input from the standard input (stdin) and buffers it
 *
 * Return:
 * Returns the number of bytes read or -1 on error.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;
    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
        r = getline(buf, &len_p, stdin);
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            *len = r;
            info->cmd_buf = (char *)malloc(r + 1);
            strcpy(info->cmd_buf, *buf);
        }
    }
    return (r);
}

/**
 * get_input - Retrieve input from standard input or buffered input
 * @info: A pointer to the info_t struct containing program information
 * Description:
 * This function retrieves input either from the standard input (stdin) or from
 * a previously buffered input.
 * Return:
 * Returns the number of bytes read or -1 on error.
 */

ssize_t get_input(info_t *info)
{
    static char buf[READ_BUF_SIZE];
    static size_t i = 0;
    size_t j = 0;
    size_t len = 0;
    ssize_t r = 0;

    char *p = NULL;

    r = read_buf(info, buf, &i);
    if (r == -1)
    {
        return -1;
    }

    if (len)
    {
        j = i;
        p = buf + i;
        check_chain(buf, &j, i, len);
        while (j < len)
        {
            if (is_chain(buf, &j))
            {
                break;
            }
            j++;
        }
        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }
        return (ssize_t)strlen(p);
    }
    info->cmd_buf = (char *)malloc(strlen(buf) + 1);
    if (info->cmd_buf != NULL) {
        strcpy(info->cmd_buf, buf);
    } else {
    }
    p = NULL;
    return r;
}

/**
 * launch_shell - Entry point of the shell program
 * Description:
 * The `launch_shell` function is the entry point of the shell program. It manages the
 * main loop of the shell, which repeatedly prompts the user input, processes
 * exits the shell by entering the "exit" command.
 *
 * Return:
 * Returns 0 upon successful execution.
 */

int launch_shell(void)
{
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    int num_args;
    while (1)
    {
        printf("Shell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        split_input(input, args, &num_args);
        if (num_args > 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            }
            else if (pid < 0)
            {
                perror("fork");
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }
    return (0);
}


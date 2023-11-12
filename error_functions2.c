#include "shell.h"


/**
 * _eputs - this function will print an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void _eputs(char *str)
{
	int t = 0;
if (!str)
return;
	while (str[t] != '\0')
	{
	_eputchar(str[t]);
	t++;
	}
}

/**
 * _eputchar - this funtion will write the character a to stderr
 * @a: The character to print
 * Return: On success 1 and or error -1
 */

int _eputchar(char a)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];
if (a == BUF_FLUSH || t >= WRITE_BUF_SIZE)
{
	write(2, buf, t);
	t = 0;
}
	if (a != BUF_FLUSH)
	buf[t++] = a;
	return (1);
}

/**
 * _putfd - this funtion will write the character a to given fd
 * @a: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1 and -1 on error
 */

int _putfd(char a, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];
if (a == BUF_FLUSH || t >= WRITE_BUF_SIZE)
{
	write(fd, buf, t);
	t = 0;
}
	if (a != BUF_FLUSH)
	buf[t++] = a;
	return (1);
}

/**
 * _putsfd - this function will print an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars
 */

int _putsfd(char *str, int fd)
{
	int t = 0;
	if (!str)
	return (0);
while (*str)
{
	t += _putfd(*str++, fd);
}
	return (t);
}



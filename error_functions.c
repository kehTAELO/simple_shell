#include "shell.h"


/**
 * _erratoi - this function converts a string to an integer
 * @a: the string to be converted
 * Return: 0 if no numbers in string
 */

int _erratoi(char *a)
{
	int t = 0;
	unsigned long int result = 0;
		if (*a == '+')
	a++;  /* TODO: why does this make main return 255? */
		for (t = 0;  a[t] != '\0'; t++)
{
	if (a[t] >= '0' && a[t] <= '9')
{
	result *= 10;
	result += (a[t] - '0');
	if (result > INT_MAX)
	return (-1);
}
	else
	return (-1);
}
	return (result);
}

/**
 * print_error - this funtion prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 * print_d - this function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int t, count = 0;
	unsigned int _abs_, current;
		if (fd == STDERR_FILENO)
	__putchar = _eputchar;
		if (input < 0)
	{
	_abs_ = -input;
	__putchar('-');
	count++;
}
	else
	_abs_ = input;
	current = _abs_;
	for (t = 1000000000; t > 1; t /= 10)
{
	if (_abs_ / t)
{
	__putchar('0' + current / t);
	count++;
}
	current %= t;
}
	__putchar('0' + current);
	count++;
	return (count);
}


/**
 * convert_number - this is a converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: a string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
	n = -num;
	sign = '-';
}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
	*--ptr = array[n % base];
	n /= base;
} while
(n != 0);
	if (sign)
	*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - this function will replace first instance of '#' with '\0'
 * @buf: this is the address of the string to modify
 * Return: Always 0
 */

void remove_comments(char *buf)
{
	int c;
for (c = 0; buf[c] != '\0'; c++)
	if (buf[c] == '#' && (!c || buf[c - 1] == ' '))
{
	buf[c] = '\0';
	break;
}
}

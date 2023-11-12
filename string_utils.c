#include "shell.h"


/**
 * _strlen - this function returns the length of a string
 * @q: the string whose length to check
 * Return: integer
 */

int _strlen(char *q)
{
	int t = 0;

	if (!q)

	return (0);
	while (*q++)
	t++;
	return (t);
}


/**
 * _strcmp - this function performs A comparison of two strangs.
 * @d1: the first strang
 * @d2: the second strang
 * Return: posetive if d1 > d2 and negative if d1 < d2
 */

int _strcmp(char *d1, char *d2)
{
	while (*d1 && *d2)
{
	if (*d1 != *d2)
	return (*d1 - *d2);
	d1++;
	d2++;
}
	if (*d1 == *d2)
	return (0);
	else
	return (*d1 < *d2 ? -1 : 1);
}


/**
 * starts_with - this function checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	if (*needle++ != *haystack++)
	return (NULL);
	return ((char *)haystack);
}


/**
 * _strcat - this function concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	dest++;
	while (*src)
	*dest++ = *src++;
	*dest = *src;
	return (ret);
}

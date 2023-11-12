#include "shell.h"


/**
 **_strncpy - this function will copy a string or strings.
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int t, c;
	char *p = dest;
t = 0;
	while (src[t] != '\0' && t < n - 1)
{
	dest[t] = src[t];
	t++;
}
	if (t < n)
{
	c = t;
	while (c < n)
{
	dest[c] = '\0';
	c++;
}
}
	return (p);
}

/**
 **_strncat - this function will concatenates two strings
 *@dest: this is the first string
 *@src: this will be second string
 *@n: this is the amount of bytes to be maximally used
 *Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int t, c;
	char *p = dest;
t = 0;
	c = 0;
	while (dest[t] != '\0')
	t++;
	while (src[c] != '\0' && c < n)
{
	dest[c] = src[c];
	t++;
	c++;
}
	if (c < n)
	dest[t] = '\0';
	return (p);
}

/**
 **_strchr - this funcion locates a character in a string
 *@p: the string to be parsed
 *@c: the character to look for
 *Return: (s) which is a pointer to the memory
 */

char *_strchr(char *p, char c)
{
	do {
	if (*p == c)
	return (p);
	} while (*p++ != '\0');
	return (NULL);
}



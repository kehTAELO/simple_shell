#include "shell.h"


/**
 * _memset - this function fills memory with a constant byte
 * @w: the pointer to the memory area
 * @d: the byte to fill *s with
 * @f: the amount of bytes to be filled
 * Return: (w) a pointer to the memory area s
 */

char *_memset(char *w, char d, unsigned int f)
{
	unsigned int t;
for (t = 0; t < f; t++)
	w[t] = d;
return (w);
}


/**
 * ffree - this function frees a string of strings
 * @tt: the string of strings
 */

void ffree(char **tt)
{
	char **a = tt;
if (!tt)
	return;
while (*tt)
	free(*tt++);
free(a);
}


/**
 * _realloc - this function reallocates a block of memory
 * @ptr: the pointer to previous malloc'ated block
 * @old_size: the byte size of previous block
 * @new_size: the byte size of new block
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *c;

	if (!ptr)

	return (malloc(new_size));
	if (!new_size)
	return (free(ptr), NULL);
if (new_size == old_size)
	return (ptr);
c = malloc(new_size);
	if (!c)
	return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	c[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (c);
}

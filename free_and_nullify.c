#include "shell.h"

/**
 * bfree - this function frees a pointer
 * @ptr: the address of the pointer
 * Return: 1
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}
	return (0);
}

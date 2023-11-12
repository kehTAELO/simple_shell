#include "shell.h"


/**
 * _myenv - this function will print the current environment
 * @info: the Structure contains potential arguments
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - this function gets the value of an environ variable
 * @info: this Structure contains potential arguments
 * @name: env var name
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *c;
while (node)
	{
	c = starts_with(node->str, name);
	if (c && *c)
	return (c);
	node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - this structure will Initialize a new environment variable.
 * @info: this Structure contains potential arguments
 *  Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
	_eputs("Incorrect number of arguements\n");
	return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}


/**
 * _myunsetenv - this function will Remove an environment variable
 * @info: this structure contains potential arguments
 * Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int c;
if (info->argc == 1)
{
	_eputs("Too few arguements.\n");
	return (1);
	}
	for (c = 1; c <= info->argc; c++)
	_unsetenv(info, info->argv[c]);
	return (0);
}


/**
 * populate_env_list - this function populates env linked list
 * @info: this Structure contains potential arguments.
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t t;
		for (t = 0; environ[t]; t++)
	add_node_end(&node, environ[t], 0);
info->env = node;
	return (0);
}




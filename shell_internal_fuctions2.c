#include "shell.h"

/**
 * _myhistory - this function displays the history list
 * @info: this Structure contains potential arguments
 *  Return: Always 0
 */

int _myhistory(info_t *info)

{
	print_list(info->history);
	return (0);
}


/**
 * unset_alias - this function sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success
 */

int unset_alias(info_t *info, char *str)

{
	char *t, m;
	int ret;
t = _strchr(str, '=');
	if (!t)
	return (1);
	m = *t;
	*t = 0;
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*t = m;
	return (ret);

}


/**
 * set_alias - this funtion sets alias to string
 * @str: the string alias
 * @info: parameter struct
 * Return: Always 0 on success
 */

int set_alias(info_t *info, char *str)

{
	char *t;
t = _strchr(str, '=');
	if (!t)
	return (1);
	if (!*++t)
	return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias - this function prints an alias string
 * @node: the alias node
 * Return: Always 0 on success
 */

int print_alias(list_t *node)

{
	char *t = NULL, *c = NULL;
if (node)
{
	t = _strchr(node->str, '=');
	for (c = node->str; c <= t; c++)
	_putchar(*c);
	_putchar('\'');
	_puts(t + 1);
	_puts("'\n");
	return (0);
}
	return (1);
}


/**
 * _myalias - this function mimics the alias builtin
 * @info: this structure contains potential arguments
 *  Return: Always 0
 */

int _myalias(info_t *info)

{
	int t = 0;
	char *m = NULL;
	list_t *node = NULL;
		if (info->argc == 1)
	{
		node = info->alias;
	while (node)
	{
		print_alias(node);
		node = node->next;
	}
		return (0);
	}
	for (t = 1; info->argv[t]; t++)
	{
		m = _strchr(info->argv[t], '=');
if (m)
set_alias(info, info->argv[t]);
else
	print_alias(node_starts_with(info->alias, info->argv[t], '='));
	}
	return (0);
}

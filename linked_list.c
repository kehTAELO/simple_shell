#include "shell.h"


/**
 * add_node - this function adds a node to the start of the list
 * @head: the address of pointer to head node
 * @str: the str field of node
 * @num: the node index used by history
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;
if (!head)
	return (NULL);
new_head = malloc(sizeof(list_t));
	if (!new_head)
	return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
{
	new_head->str = _strdup(str);
	if (!new_head->str)
{
	free(new_head);
	return (NULL);
}
}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}


/**
 * add_node_end - this function adds a node to the end of the list
 * @head: the address of pointer to head node
 * @str: the str field of node
 * @num: the node index used by history
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;
if (!head)
	return (NULL);
node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
{
	new_node->str = _strdup(str);
	if (!new_node->str)
{
	free(new_node);
	return (NULL);
}
}
	if (node)
{
	while (node->next)
	node = node->next;
	node->next = new_node;
}
	else
	*head = new_node;
	return (new_node);
}


/**
 * print_list_str - this function prints only the str element
 * @w: the pointer to first node
 * Return: the size of list
 */

size_t print_list_str(const list_t *w)
{
	size_t t = 0;
while (w)
{
	_puts(w->str ? w->str : "(nil)");
	_puts("\n");
	w = w->next;
	t++;
}
	return (t);
}


/**
 * delete_node_at_index - this function deletes node at given index
 * @head: the address of pointer to first node
 * @index: the index of node to delete
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int c = 0;
if (!head || !*head)
	return (0);
if (!index)
{
	node = *head;
	*head = (*head)->next;
	free(node->str);
	free(node);
	return (1);
}
	node = *head;
	while (node)
{
	if (c == index)
{
	prev_node->next = node->next;
	free(node->str);
	free(node);
	return (1);
}
	c++;
	prev_node = node;
	node = node->next;
}
	return (0);
}


/**
 * free_list - this function frees all nodes of a list
 * @head_ptr: the address of pointer to head node
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;
if (!head_ptr || !*head_ptr)
	return;
head = *head_ptr;
	node = head;
	while (node)
{
	next_node = node->next;
	free(node->str);
	free(node);
	node = next_node;
}
	*head_ptr = NULL;
}

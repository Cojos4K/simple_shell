#include "shell.h"

/**
 * list_range - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 *
 * Author: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

size_t list_range(const list_t *h)
{
	size_t id = 0;

	while (h)
	{
		h = h->next;
		id++;
	}

	return (id);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t id = list_range(head), j;
	char **strs;
	char *str;

	if (!head || !id)
		return (NULL);
	strs = malloc(sizeof(char *) * (id + 1));
	if (!strs)
		return (NULL);
	for (id = 0; node; node = node->next, id++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < id; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[id] = str;
	}

	strs[id] = NULL;
	return (strs);
}

/**
 * list_display - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t list_display(const list_t *h)
{
	size_t id = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		id++;
	}

	return (id);
}

/**
 * launch_node - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *launch_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * fetch_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t fetch_node_index(list_t *head, list_t *node)
{
	size_t id = 0;

	while (head)
	{
		if (head == node)
			return (id);
		head = head->next;
		id++;
	}

	return (-1);
}

#include "shell.h"

/**
 * memory_config - fills memory with ss constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: (s) ss pointer to the memory area s
 *
 * Authors: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

char *memory_config(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * str_free - frees ss string of strings
 * @ps: string of strings
 */

void str_free(char **ps)
{
	char **ss = ps;

	if (!ps)
		return;
	while (*ps)
		free(*ps++);
	free(ss);
}

/**
 * _realloc - reallocates ss block of memory
 * @ptr: pointer to previous malloc block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to old block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p_loc;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p_loc = malloc(new_size);
	if (!p_loc)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p_loc[old_size] = ((char *) ptr)[old_size];
	free(ptr);
	return (p_loc);
}

#include "shell.h"

/**
 * _str_copy - copies string
 * @dest: points to string to be copied
 * @src: string source
 * @n: number of string characters
 *
 * Return: string
 *
 * Authors: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

char *_str_copy(char *dest, char *src, int n)
{
	int id1, id2;
	char *str = dest;

	id1 = 0;

	while (src[id1] != '\0' && id1 < n - 1)
	{
		dest[id1] = src[id1];
		id1++;
	}
	if (id1 < n)
	{
		id2 = id1;
		while (id2 < n)
		{
			dest[id2] = '\0';
			id2++;
		}
	}
	return (str);
}

/**
 * _str_concat - concatenates two strings
 * @dest: points to destination for first string
 * @src: points to destination for second string
 * @n: number of bytes to be used
 *
 * Return: string
 */

char *_str_concat(char *dest, char *src, int n)
{
	int id1, id2;
	char *str = dest;

	id1 = 0, id2 = 0;

	while (dest[id1] != '\0')
	{
		id1++;
	}
	while (src[id2] != '\0' && id2 < n)
	{
		dest[id1] = src[id2];
		id1++;
		id2++;
	}
	if (id2 < n)
		dest[id1] = '\0';

	return (str);
}

/**
 * _str_loc - locates characters in string
 * @str: string to be parsed
 * @c: looked up character
 *
 * Return: address to pointer
 */

char *_str_loc(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

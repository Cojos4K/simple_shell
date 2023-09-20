#include "shell.h"

/**
 * _str_copy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 *
 * Authors: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

char *_str_copy(char *dest, char *src)
{
	int id = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[id])
	{
		dest[id] = src[id];
		id++;
	}

	dest[id] = 0;
	return (dest);
}

/**
 * _str_duplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_str_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int id = 0;

	if (!str)
		return;
	while (str[id] != '\0')
	{
		_putchar(str[id]);
		id++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int id;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || id >= WRITE_BUF_SIZE)
	{
		write(1, buf, id);
		id = 0;
	}

	if (c != BUF_FLUSH)
		buf[id++] = c;
	return (1);
}

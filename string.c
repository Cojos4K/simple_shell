#include "shell.h"

/**
 * _str_len - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 *
 * Authors: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

int _str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str++)
		i++;
	return (i);
}

/**
 * _str_cmp - compares of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2,
 * and zero if str1 == str2
 */

int _str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * initializer - checks if needle starts with stack
 * @stack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of stack or NULL
 */

char *initializer(const char *stack, const char *needle)
{
	while (*needle)
		if (*needle++ != *stack++)
			return (NULL);
	return ((char *) stack);
}

/**
 * _str_concat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */

char *_str_concat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

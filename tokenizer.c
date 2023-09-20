#include "shell.h"

/**
 * _str_token - splits string into words
 * @str: the input string
 * @d: the delimeter string
 *
 * Return: array pointer to strings, or NULL on failure
 *
 * Authors: Frederick Baafi & Bryan Wellington Sam
 */

char **_str_token(char *str, char *d)
{
	int id1, id2, id3, id4, n_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (id1 = 0; str[id1] != '\0'; id1++)
		if (!is_delim(str[id1], d) && (is_delim(str[id1 + 1], d) || !str[id1 + 1]))
			n_words++;
	if (n_words == 0)
		return (NULL);
	s = malloc((1 + n_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (id1 = 0, id2 = 0; id2 < n_words; id2++)
	{
		while (is_delim(str[id1], d))
			id1++;
		id3 = 0;
		while (!is_delim(str[id1 + id3], d) && str[id1 + id3])
			id3++;
		s[id2] = malloc((id3 + 1) * sizeof(char));
		if (!s[id2])
		{
			for (id3 = 0; id3 < id2; id3++)
				free(s[id3]);
			free(s);
			return (NULL);
		}

		for (id4 = 0; id4 < id3; id4++)
			s[id2][id4] = str[id1++];
		s[id2][id4] = 0;
	}

	s[id2] = NULL;
	return (s);
}

/**
 * _str_ntoken - splits a string into words
 * @str: the input string
 * @d: the delimeter
 *
 * Return: array pointer to strings, or NULL on failure
 */

char **_str_ntoken(char *str, char d)
{
	int id1, id2, id3, id4, n_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (id1 = 0; str[id1] != '\0'; id1++)
		if ((str[id1] != d && str[id1 + 1] == d) ||
			(str[id1] != d && !str[id1 + 1]) || str[id1 + 1] == d)
			n_words++;
	if (n_words == 0)
		return (NULL);
	s = malloc((1 + n_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (id1 = 0, id2 = 0; id2 < n_words; id2++)
	{
		while (str[id1] == d && str[id1] != d)
			id1++;
		id3 = 0;
		while (str[id1 + id3] != d && str[id1 + id3] && str[id1 + id3] != d)
			id3++;
		s[id2] = malloc((id3 + 1) * sizeof(char));
		if (!s[id2])
		{
			for (id3 = 0; id3 < id2; id3++)
				free(s[id3]);
			free(s);
			return (NULL);
		}

		for (id4 = 0; id4 < id3; id4++)
			s[id2][id4] = str[id1++];
		s[id2][id4] = 0;
	}

	s[id2] = NULL;
	return (s);
}

#include "shell.h"

/**
 * _char_series - test if current char in buffer is a chain delimeter
 * @info: struct parameter
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 *
 * Authors: Byran Wellington Sam & Frederick Baafi
 */

int _char_series(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_series - checks we should continue chaining based on last status
 * @info: struct parameter
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_series(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * alias_switch - replaces an aliases in the tokenized string
 * @info: struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */

int alias_switch(info_t *info)
{
	int i;
	char *p;
	list_t *node;

	for (i = 0; i < 10; i++)
	{
		node = launch_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _str_loc(node->str, '=');
		if (!p)
			return (0);
		p = _str_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}

/**
 * var_switch - replaces variables in the tokenized string
 * @info: struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */

int var_switch(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_str_cmp(info->argv[i], "$?"))
		{
			_str_switch(&(info->argv[i]),
				_str_duplicate(convert_number(info->status, 10, 0)));
			continue;
		}

		if (!_str_cmp(info->argv[i], "$$"))
		{
			_str_switch(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		node = launch_node(info->env, &info->argv[i][1], '=');
		if (node)
		{
			_str_switch(&(info->argv[i]),
				_str_duplicate(_strchr(node->str, '=') + 1));
			continue;
		}

		_str_switch(&info->argv[i], _strdup(""));
	}

	return (0);
}

/**
 * _str_switch - replaces string
 * @old: address of old string
 * @recent: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int _str_switch(char **old, char *recent)
{
	free(*old);
	*old = recent;
	return (1);
}

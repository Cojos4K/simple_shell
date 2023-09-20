#include "shell.h"

/**
 * empty_info - activates info_t struct
 * @info: points to struct
 *
 * Return: void
 *
 * Author: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

void empty_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * config_info - initialise info_t struct
 * @info: points to struct
 * @av: argument vector
 *
 * Return: void
 */

void config_info(info_t *info, char **av)
{
	int id = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (id = 0; info->argv && info->argv[id]; id++)
			;
		info->argc = id;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * _free_info - clears info_t struct fields
 * @info: struct address
 * @total: true for clearing fields
 *
 * Return: void
 */

void _free_info(info_t *info, int total)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (total)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

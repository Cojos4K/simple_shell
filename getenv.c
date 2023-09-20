#include "shell.h"

/**
 * _env_fetch - returns copy of our environ
 * @info: struct with arguments to keep function prototype
 *
 * Return: (0)
 *
 * Author: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

char **_env_fetch(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _env_deactivate - removes an environment variable
 * @info: struct with arguments to keep function prototype
 * @var: env variable property
 *
 * Return: 1 on remove and 0 otherwise
 */

int _env_deactivate(info_t *info, char *var)
{
	char *n;
	size_t id = 0;
	list_t *node = info->env;

	if (!node || !var)
		return (0);

	while (node)
	{
		n = starts_with(node->str, var);
		if (n && *n == '=')
		{
			info->env_changed = index_node_removal(&(info->env), id);
			node = info->env;
			continue
		}
		node = node->next;
		id++;
	}
	return (info->env_changed);
}

/**
 * _env_activate - activates a new env variable
 * or modifies one already there
 * @info: struct with arguments to keep function prototype
 * @var: env variable property
 * @val: env variable value
 *
 * Return: (0)
 */

int _env_activate(info_t *info, char *var, char *val)
{
	char *n;
	list_t *node;
	char *buf = NULL;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);

	if (!buf)
		return (1);

	str_copy(buf, var);
	str_concat(buf, '=');
	str_concat(buf, val);

	node = info->env;

	while (node)
	{
		n = launch_node(node->str, var);
		if (n && *n == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


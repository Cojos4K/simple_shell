#include "shell.h"

/**
 * run_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 *
 * Author: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

int run_cmd(info_t *info, char *path)
{
	struct stat st;
	(void) info;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * char_duplicate - duplicates characters
 * @str_path: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */

char *char_duplicate(char *str_path, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str_path[i] != ':')
			buf[k++] = str_path[i];
	buf[k] = 0;
	return (buf);
}

/**
 * identify_path - finds this cmd in the PATH string
 * @info: the info struct
 * @str_path: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */

char *identify_path(info_t *info, char *str_path, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!str_path)
		return (NULL);
	if ((_str_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (run_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			path = char_duplicate(str_path, curr_pos, i);
			if (!*path)
				_str_concat(path, cmd);
			else
			{
				_str_concat(path, "/");
				_str_concat(path, cmd);
			}

			if (run_cmd(info, path))
				return (path);
			if (!str_path[i])
				break;
			curr_pos = i;
		}

		i++;
	}

	return (NULL);
}

#include "shell.h"

/**
 * fetch_history_file - gets the history file
 * @info: struct parameter
 *
 * Return: str of history file
 *
 * Author: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

char *fetch_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	str_copy(buf, dir);
	str_concat(buf, "/");
	str_concat(buf, HIST_FILE);
	return (buf);
}

/**
 * record_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int record_history(info_t *info)
{
	ssize_t fd;
	char *filename = fetch_history_file(info);

	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: struct parameter
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *info)
{
	int id, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = fetch_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (id = 0; id < fsize; id++)
		if (buf[id] == '\n')
		{
			buf[id] = 0;
			initiate_history(info, buf + last, linecount++);
			last = id + 1;
		}

	if (last != id)
		initiate_history(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	reindex_history(info);
	return (info->histcount);
}

/**
 * initiate_history - adds entry to a history linked list
 * @info: struct argument to keep function prototypes
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int initiate_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * reindex_history - renumbers the history linked list after changes
 * @info: struct argument to keep function prototypes
 *
 * Return: the new histcount
 */

int reindex_history(info_t *info)
{
	list_t *node = info->history;
	int id = 0;

	while (node)
	{
		node->num = id++;
		node = node->next;
	}

	return (info->histcount = id);
}

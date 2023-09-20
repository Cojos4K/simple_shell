#include "shell.h"

/**
 * buffer_input - adds buffer to commands
 * @info: struct parameter
 * @buf: address of buffer
 * @len: address of variable length
 *
 * Return: number of bytes
 *
 * Authors: Frederick Baafi & Bryan Wellington Sam
 * Date: 09/2023
 */

ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t val = 0;
	size_t n_len = 0;

	if (!*len)
	{
		free(buf);

		*buf = NULL;
		signal(SIGINT, sigintHandler);

		if USE_GETLINE
			val = getline(buf, &n_len, stdin);
		else
			val = _getline(info, buf, &n_len);

		if (val > 0)
		{
			if ((*buf)[val - 1] == '\n')
			{
				(*buf)[val - 1] = '\0';
				val--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			initiate_history(info, *buf, info->histcount++);

			if (_str_loc(*buf, ';'))
			{
				*len = val;
				info->cmd_buf = buf;
			}
		}
	}

	return (val);
}

/**
 * fetch_input - gets a line without newline
 * @info: struct paramter
 *
 * Return: number of bytes
 */

ssize_t fetch_input(info_t *info)
{
	static char *buf;
	static size_t id1, id2, len;

	ssize_t val = 0;
	char **n_buf = &(info->arg), *n;

	_putchar(BUF_FLUSH);
	val = fetch_input(info, &buf, &len);

	if (val == -1)
		return (-1);

	if (len)
	{
		id2 = id1;
		n = buf + id1;
		check_series(info, buf, &id2, id1, len);

		while (id2 < len)
		{
			if (_char_series(info, buf, &id2))
				break;
			id2++;
		}

		id1 = id2 + 1;
		if (id1 >= len)
		{
			id1 = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*n_buf = n;

		return (_strlen(n));
	}
	*n_buf = buf;

	return (val);
}

/**
 * buffer_read - reads a buffer
 * @info: struct parameter
 * @buf: buffer
 * @s: buffer size
 *
 * Return: val
 */

ssize_t buffer_read(info_t *info, char *buf, size_t *s)
{
	ssize_t val = 0;

	if (*s)
		return (0);

	val = read(info->readfd, buf, READ_BUF_SIZE);
	if (val >= 0)
		* s = val;

	return (val);
}

/**
 * _getline - from STDIN, gets the next line
 * @info: struct parameter
 * @ptr: buffer pointer address
 * @length: pointer buffer size
 *
 * Return: string
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t id, len;
	size_t k;
	size_t r = 0, s = 0;
	char *p = NULL, *latest_p = NULL, *c;

	p = *ptr;

	if (p && length)
		s = *length;
	if (id == len)
		id = len = 0;
	r = buffer_read(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _str_loc(buf + id, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	latest_p = _realloc(p, s, s ? s + k : k + 1);

	if (!latest_p)
		return (p ? free(p), -1 : -1);
	if (s)
		str_concat(latest_p, buf + id, k - id);
	else
		str_copy(latest_p, buf + id, k - id + 1);

	s += k - id;
	id = k;
	p = latest_p;

	if (length)
		* length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - prevents ctrl C effect
 * @sig_num: signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

#include "shell.h"


/**
 * input_buf - this function buffers a chained command
 * @info: the parameter struct
 * @buf: the address of buffer
 * @len: the address of len var
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t t = 0;
	size_t len_p = 0;
if (!*len)
{
	free(*buf);
	*buf = NULL;
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	t = getline(buf, &len_p, stdin);
#else
	t = _getline(info, buf, &len_p);
#endif
	if (t > 0)
{
	if ((*buf)[t - 1] == '\n')
{
	(*buf)[t - 1] = '\0';
	t--;
}
	info->linecount_flag = 1;
	remove_comments(*buf);
	build_history_list(info, *buf, info->histcount++);
{
	*len = t;
	info->cmd_buf = buf;
}
}
}
	return (t);
}


/**
 * get_input - this function gets a line and will minus the newline
 * @info: the parameter struct
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t t, c, len;
	ssize_t q = 0;
	char **buf_p = &(info->arg), *w;
_putchar(BUF_FLUSH);
	q = input_buf(info, &buf, &len);
if (q == -1)
	return (-1);
if (len)
{
	c = t;
	w = buf + t;
	check_chain(info, buf, &c, t, len);
	while (c < len)
{
	if (is_chain(info, buf, &c))
	break;
	c++;
}
	t = c + 1;
	if (t >= len)
{
	t = len = 0;
	info->cmd_buf_type = CMD_NORM;
}
	*buf_p = w;
	return (_strlen(w));
}
	*buf_p = buf;
	return (q);

}


/**
 * read_buf - this finnctipn will read a buffer
 * @info: the parameter struct
 * @buf: the buffer
 * @a: size
 * Return: t
 */

ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
	ssize_t t = 0;
if (*a)
return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
	*a = t;
return (t);
}


/**
 * _getline - this function gets the next line of input
 * @info: the parameter struct
 * @ptr: the address of pointer to buffer
 * @length: the size of preallocated ptr
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t k;
	ssize_t q = 0, s = 0;
	char *r = NULL, *new_p = NULL, *c;
r = *ptr;
if (r && length)
s = *length;
	if (t == len)
	t = len = 0;
	q = read_buf(info, buf, &len);
	if (q == -1 || (q == 0 && len == 0))
	return (-1);
	c = _strchr(buf + t, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(r, s, s ? s + k : k + 1);
	if (!new_p)
	return (r ? free(r), -1 : -1);
	if (s)
	_strncat(new_p, buf + t, k - t);
	else
	_strncpy(new_p, buf + t, k - t + 1);
	s += k - t;
	t = k;
	r = new_p;
	if (length)
	*length = s;
	*ptr = r;
	return (s);
}

/**
 * sigintHandler - this function blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

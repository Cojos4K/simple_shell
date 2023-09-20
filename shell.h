#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * Author: Bryan Wellington Sam & Frederick Baafi
 * Date:09/2023 
 * struct liststr - Singly linked list
 * @num: The number field
 * @str: A string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: An string generated from getline containing arguements
 * @argv:An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The argument count
 * @line_count: The error count
 * @err_num: The error code for exit()s
 * @linecount_flag: If on count this line of input
 * @fname: The program filename
 * @env: Linked list local copy of environ
 * @environ: Custom modified copy of environ from LL env
 * @history: The history node
 * @alias: The alias node
 * @env_changed: On if environ was changed
 * @status: The return status of the last exec'd command
 * @cmd_buf: Address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The fd from which to read line input
 * @histcount: The history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int cfshell(info_t *info, char **av);
int find_builtin(info_t *info);
void cmd_pathfind(info_t *info);
void cmd_fork(info_t *info);

/* toem_parser.c */
int run_cmd(info_t *info, char *path);
char *char_duplicate(char *str_path, int start, int stop);
char *identify_path(info_t *info, char *str_path, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _str_len(char *str);
int _str_cmp(char *str1, char *str2);
char *initializer(const char *stack, const char *needle);
char *_str_concat(char *dest, char *src);

/* toem_string1.c */
char *_str_copy(char *dest, char *src);
char *_str_duplicate(const char *str);
void _puts(char *str);
int _putchar(char c);

/* toem_exits.c */
char *_str_copy(char *dest, char *src, int n);
char *_str_concat(char *dest, char *src, int n);
char *_str_loc(char *str, char c);

/* toem_tokenizer.c */
char **str_token(char *str, char *d);
char **str_ntoken(char *str, char d);

/* toem_realloc.c */
char *memory_config(char *s, char b, unsigned int n);
void str_free(char **ps);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* toem_memory.c */
int ptr_free(void **ptr);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t buffer_input(info_t *info, char **buf, size_t *len);
ssize_t fetch_input(info_t *info);
int _getline(info_t *info, char **ptr, size_t *length);
ssize_t buffer_read(info_t *info, char *buf, size_t *s);
void sigintHandler(int sig_num);

/* toem_getinfo.c */
void empty_info(info_t *info);
void config_info(info_t *info, char **av);
void _free_info(info_t *info, int total);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **_env_fetch(info_t *info);
int _env_deactivate(info_t *info, char *var);
int _env_activate(info_t *info, char *var, char *val);

/* toem_history.c */
char *fetch_history_file(info_t *info);
int record_history(info_t *info);
int read_history(info_t *info);
int initiate_history(info_t *info, char *buf, int linecount);
int reindex_history(info_t *info);

/* toem_lists.c */
list_t *attach_node(list_t **head, const char *str, int n);
list_t *attach_end_node(list_t **head, const char *str, int n);
size_t strlog_display(const list_t *h);
int index_node_removal(list_t **head, unsigned int index);
void free_list(list_t **ptr);

/* toem_lists1.c */
size_t list_range(const list_t *h);
char **list_to_strings(list_t *head);
size_t list_display(const list_t *h);
list_t *launch_node(list_t *node, char *prefix, char c);
ssize_t fetch_node_index(list_t *head, list_t *node);

/* toem_vars.c */
int _char_series(info_t *info, char *buf, size_t *p);
void check_series(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int alias_switch(info_t *info);
int var_switch(info_t *info);
int _str_switch(char **old, char *recent);

#endif


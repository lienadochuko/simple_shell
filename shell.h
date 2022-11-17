#ifndef SHELLH
#define SHELLH

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "history.h"
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "shellvars.h"
/*#include <string.h>*/

/* from in.c */
int shintmode(void);


/* from _printenv.c */
int _printenv(void);

/**
 * struct passinfo - contains pseudo-arguments to pass into a function
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * l@inecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*from cmdcall.c */
int builtincall(char *av[]);
int cmdcall(char *av[], char *path);

/* from parser.c */
int parseargs(char **buf);

/* from errhandl.c */
int errhandl(int status);

/* from _getenv.c and getenviron.c */
char ***getenviron(void);
int setallenv(char **environ, char *add);
char *_getenv(char *avzero);
int _setenv(char *name, char *val);
int _unsetenv(char *name);
char **getallenv(void);

/* from string.c */
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *, char *);
char *_strdup(char *str);
char *_strcat(char *a, char *b);

/* from utility.c */
char *itos(int digits);
char *_strchr(char *s, char c);
int fprintstrs(int fd, char *str, ...);
int printerr(char *);
int linecount(int);

/* from cd.c */
int _cd(char *av[]);

/* from alias.c */
int aliascmd(char **av);
char *getalias(char *name);
int unsetalias(char *name);

/* from shellvars.c */
int initsvars(int ac, char **av);
char *getsvar(char *name);
int setsvar(char *name, char *val);
int unsetsvar(char *name);
ShellVar **getspecial(void);
ShellVar **getvars(void);

/* from _realloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* from _strtok.c */
char *strtok(char *str, char *delim);

/* from _getline.c */
int _getline(char **lineptr, int fd);

char *strtokqe(char *str, char *delim, int escflags);


/* from _printenv.c */
int _printenv(void);
int _putchar(char c);

/*from history.c*/
int sethist(char *cmd);
int print_hist(void);
int exit_hist(void);

/*from help.c*/
int help(char *cmd);

/* from exitcleanup.c */
void exitcleanup(char **av);

/* from _atoi*/
int _atoi(char *s);

char *_getpid(void);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);`

#endif

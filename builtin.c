#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: structure containing potential arguments. Used to maintain constant function prototype
 * Return: exits with a given exit status (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;
	if (info->argv[1]) /* if there is an exit argument */
		exitcheck = _errr

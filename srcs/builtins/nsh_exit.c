#include "../includes/nsh.h"

int	nsh_exit(t_sh *nsh, char **args)
{
	//should free everything... maybe reconfigure builtins to accept nsh instead env
	(void)nsh;
	args[0][0] = args[0][0];
	exit(EXIT_SUCCESS);
	return (0);
}
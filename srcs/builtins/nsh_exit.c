#include "../includes/nsh.h"

void	free_everything(t_sh *nsh)
{
	free_array(nsh->bui->str);
}

int	nsh_exit(t_sh *nsh, char **args)
{
	free_everything(nsh);
	(void)args;
	exit(EXIT_SUCCESS);
	return (0);
}

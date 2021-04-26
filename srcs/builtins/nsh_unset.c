#include "../includes/nsh.h"

int	nsh_unset(t_sh *nsh, char **args)
{
	int	i;
	t_env	*node;

	i = 1;
	while (args[i])
	{
		node = NULL;
		if ((node = find_by_name(nsh->env, args[i])))
			remove_var(nsh->env, node);
		i++;
	}
	return (0);
}
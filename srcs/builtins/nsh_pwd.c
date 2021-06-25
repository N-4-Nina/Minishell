#include "../includes/nsh.h"

int	nsh_pwd(t_sh *nsh, char **args)
{
	t_env	*var;

	args[0][0] = 'p';
	var = find_by_name(nsh->env, "PWD");
	write(1, var->value, ft_strlen(var->value));
	write(1, "\n", 1);
	return (0);
}

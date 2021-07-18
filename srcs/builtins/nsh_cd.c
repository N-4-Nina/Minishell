#include "../../includes/nsh.h"

int	nsh_cd(t_sh *nsh, char **args)
{
	t_env	*var;

	if (!chdir(args[1]))
	{
		var = find_by_name(nsh->env, "PWD");
		getcwd(var->value, 4096);
	}
	*(nsh->last_status) = 0;
	return (0);
}

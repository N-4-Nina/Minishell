#include "../includes/nsh.h"

int	nsh_export(t_sh *nsh, char **args)
{
	int		i;
	char	**split;
	t_env	*node;

	i = 1;
	while (args[i])
	{
		split = ft_split(args[i], '=');
		node = find_by_name(nsh->env, split[0]);
		if (node)
		{
			free(node->value);
			free(node->name);
			node->name = split[0];
			node->value = split[1];
		}
		else
			add_var(nsh->env, split[0], split[1]);
		i++;
	}
	*(nsh->last_status) = 0;
	return (0);
}

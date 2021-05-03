#include "../includes/nsh.h"

int	nsh_export(t_sh *nsh, char **args)
{
	int	i;
	char	**split;
	t_env	*node;

	i = 1;
	while(args[i])
	{
		split = ft_split(args[i], '=');
		if ((node = find_by_name(nsh->env, split[0])))
		{
			free(node->value);
			free(node->name);
			node->name = split[0];
			node->value = split[1];
		}
		else
			add_var(nsh->env, split[0], split[1]);
		printf("%s / %s \n", split[0], split[1]);
		i++;
	}
	return (0);
}
#include "../includes/nsh.h"

void	replace_or_create(t_sh *nsh, char **args, int i, int j)
{
	char	*sub;
	t_env	*node;

	sub = ft_substr(args[i], 0, j++);
	node = find_by_name(nsh->env, sub);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(&args[i][j]);
	}
	else
	{
		add_var(nsh->env, sub, &args[i][j]);
		free(sub);
	}
}

int	nsh_export(t_sh *nsh, char **args)
{
	int		i;
	int		j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (!args[i][j] || j == 0)
		{
			i++;
			continue ;
		}
		replace_or_create(nsh, args, i, j);
		i++;
	}
	return (0);
}

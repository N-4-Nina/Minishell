#include "../includes/nsh.h"

void	actually_export(t_sh *nsh, char *var, char *val)
{
	t_env	*node;

	node = find_by_name(nsh->env, var);
	if (node)
	{
		free(node->value);
		free(node->name);
		node->name = ft_strdup(var);
		node->value = ft_strdup(val);
	}
	else
		add_var(nsh->env, var, val);
}

int	nsh_export(t_sh *nsh, char **args)
{
	int		i;
	int		j;
	char	*var;
	char	*val;

	i = 0;
	while (args[++i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (!args[i][j])
			continue ;
		var = ft_substr(args[i], 0, j);
		val = ft_substr(&args[i][j + 1], 0, ft_strlen(&args[i][j + 1]));
		actually_export(nsh, var, val);
		free(var);
		free(val);
	}
	*(nsh->last_status) = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 07:51:46 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 08:31:14 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	nsh_export_env(t_sh *nsh)
{
	t_env	*lst;

	lst = nsh->env;
	while (lst)
	{
		write(1, "declare -x ", 12);
		write(1, lst->name, ft_strlen(lst->name));
		write(1, "=", 1);
		write(1, "\"", 1);
		write(1, lst->value, ft_strlen(lst->value));
		write(1, "\"", 1);
		write(1, "\n", 1);
		lst = lst->next;
	}
	*(nsh->last_status) = 0;
	return (0);
}

int	is_valid_idenfier(t_sh *nsh, char *s)
{
	if (ft_isdigit(s[0]) || s[0] == '=')
	{
		printf("Nsh: export: \'%s\': not a valid identifier\n", s);
		*(nsh->last_status) = 1;
		return (0);
	}
	return (1);
}

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
	*(nsh->last_status) = 0;
	if (!args[1])
		return (nsh_export_env(nsh));
	while (args[++i])
	{
		j = 0;
		if (!is_valid_idenfier(nsh, args[i]))
			continue ;
		while (args[i][j] && args[i][j] != '=')
			j++;
		var = ft_substr(args[i], 0, j);
		val = ft_substr(&args[i][j + 1], 0, ft_strlen(&args[i][j + 1]));
		actually_export(nsh, var, val);
		free(var);
		free(val);
	}
	return (*(nsh->last_status));
}

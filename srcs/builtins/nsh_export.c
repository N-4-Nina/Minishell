/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 07:51:46 by chpl              #+#    #+#             */
/*   Updated: 2021/08/26 13:30:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/builtins.h"
#include "../includes/arrays.h"

int	nsh_export_env(t_sh *nsh)
{
	char	**arr;
	int		size;
	int		i;
	int		j;

	i = 0;
	arr = env_to_array(nsh->env, &size);
	sort_array(arr, size);
	while (arr[i])
	{
		j = 0;
		write(1, "declare -x ", 12);
		while (arr[i][j] != '=')
			write(1, &arr[i][j++], 1);
		write(1, "=\"", 2);
		while (arr[i][++j])
			write(1, &arr[i][j], 1);
		write(1, "\"\n", 2);
		i++;
	}
	free_array(arr, size);
	*(nsh->last_status) = 0;
	return (0);
}

int	not_valid(t_sh *nsh, char *var, char *val, char **args)
{
	if (!var[0])
		printf("Nsh: export: \'=%s\': not a valid identifier\n", val);
	else
		printf("Nsh: export: \'%s\': not a valid identifier\n", var);
	*(nsh->last_status) = 1;
	free(var);
	free(val);
	nsh_mute_unset(nsh, args);
	return (0);
}

int	is_valid_idenfier(t_sh *nsh, char *var, char *val, char **args)
{
	int	i;

	i = 0;
	if (!var[i])
		return (not_valid(nsh, var, val, args));
	if (ft_isdigit(var[0]))
		return (not_valid(nsh, var, val, args));
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
			return (not_valid(nsh, var, val, args));
		i++;
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
	free(var);
	free(val);
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
		val = ft_strchr(args[i], '=');
		j = (int)(val - args[i]);
		if (!val || !args[i][j])
			continue ;
		var = ft_substr(args[i], 0, j);
		if ((size_t)j < ft_strlen(args[i]))
			val = ft_substr(&args[i][j + 1], 0, ft_strlen(&args[i][j + 1]));
		else
			val = ft_substr(&args[i][j], 1, 0);
		if (!is_valid_idenfier(nsh, var, val, args))
			break ;
		actually_export(nsh, var, val);
	}
	return (*(nsh->last_status));
}

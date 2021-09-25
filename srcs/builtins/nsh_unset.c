/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:15:48 by chpl              #+#    #+#             */
/*   Updated: 2021/09/25 11:51:26 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "environment.h"
#include "utils.h"

int	unset_valid_idenfier(char *var)
{
	int	i;

	i = 0;
	if (!var[i])
		return (0);
	if (ft_isdigit(var[0]))
		return (0);
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	nsh_mute_unset(t_sh *nsh, char **args)
{
	int		i;
	t_env	*node;

	i = 1;
	while (args[i])
	{
		if (!unset_valid_idenfier(args[i]))
			break ;
		node = NULL;
		node = find_by_name(nsh->env, args[i]);
		if (node)
			remove_var(&nsh->env, node);
		i++;
	}
	return (0);
}

int	nsh_unset(t_sh *nsh, char **args)
{
	int		i;
	int		ret;
	t_env	*node;

	i = 1;
	ret = 0;
	while (args[i])
	{
		if (!unset_valid_idenfier(args[i]))
		{
			ret = 1;
			display_error("Nsh: unset: `", args[i],
				"': not a valid identifier\n");
			i++;
			continue ;
		}
		node = NULL;
		node = find_by_name(nsh->env, args[i]);
		if (node)
			remove_var(&nsh->env, node);
		i++;
	}
	return (ret);
}

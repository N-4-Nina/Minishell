/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:38 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 14:45:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/builtins.h"
#include "../includes/utils.h"

char	*get_target(t_sh *nsh, char **args)
{
	t_env	*home;

	if (!args[1])
	{
		home = find_by_name(nsh->env, "HOME");
		if (!home)
		{
			display_error("NSH: cd: HOME not set\n", "", "");
			return (NULL);
		}
		else
			return (ft_strdup(home->value));
	}
	else
		return (ft_strdup(args[1]));
}

int	cd_args_error(t_sh *nsh, char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		*(nsh->last_status) = 1;
		display_error("Nsh: cd: too many arguments\n", "", "");
		return (1);
	}
	return (0);
}

void	update_pwd(t_sh *nsh)
{
	char	*cdn;
	t_env	*var;

	var = find_by_name(nsh->env, "PWD");
	cdn = get_current_dir_name();
	if (var)
	{
		free(var->value);
		var->value = cdn;
	}
	else
	{
		add_var(nsh->env, "PWD", cdn);
		free(cdn);
	}
}

int	nsh_cd(t_sh *nsh, char **args)
{
	char	*target;

	if (cd_args_error(nsh, args))
		return (*(nsh->last_status));
	target = get_target(nsh, args);
	if (!target)
		return (*(nsh->last_status) = 1);
	if (!chdir(target))
	{
		update_pwd(nsh);
		free(target);
		*(nsh->last_status) = 0;
		return (*(nsh->last_status));
	}
	display_error("Nsh: cd: ", target, ": No such file or directory\n");
	free(target);
	*(nsh->last_status) = 1;
	return (*(nsh->last_status));
}

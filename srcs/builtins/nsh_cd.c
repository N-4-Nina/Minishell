/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:38 by chpl              #+#    #+#             */
/*   Updated: 2021/08/20 18:35:42 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/builtins.h"
#include "../includes/utils.h"

int	cd_mulitples_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("Nsh: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

int	nsh_cd(t_sh *nsh, char **args)
{
	t_env	*var;

	if (cd_mulitples_args(args))
	{
		*(nsh->last_status) = 1;
		return (*(nsh->last_status));
	}
	var = find_by_name(nsh->env, "PWD");
	if (!chdir(args[1]))
	{
		if (var)
			var->value = get_current_dir_name();
		*(nsh->last_status) = 0;
		return (*(nsh->last_status));
	}
	printf("Nsh: cd: %s: No such file or directory\n", args[1]);
	*(nsh->last_status) = 1;
	return (*(nsh->last_status));
}

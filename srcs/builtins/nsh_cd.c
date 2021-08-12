/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:38 by chpl              #+#    #+#             */
/*   Updated: 2021/08/11 19:12:12 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/builtins.h"

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
	char	*buf;

	if (cd_mulitples_args(args))
	{
		*(nsh->last_status) = 1;
		return (*(nsh->last_status));
	}
	var = find_by_name(nsh->env, "PWD");
	if (var)
		buf = var->value;
	if (!chdir(args[1]))
	{
		getcwd(buf, 4096);
		*(nsh->last_status) = 0;
		return (*(nsh->last_status));
	}
	*(nsh->last_status) = 1;
	return (*(nsh->last_status));
}

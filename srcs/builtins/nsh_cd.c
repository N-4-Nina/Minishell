/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:38 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 15:08:57 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/builtins.h"

int	nsh_cd(t_sh *nsh, char **args)
{
	t_env	*var;

	if (!chdir(args[1]))
	{
		var = find_by_name(nsh->env, "PWD");
		getcwd(var->value, 4096);
	}
	*(nsh->last_status) = 0;
	return (0);
}

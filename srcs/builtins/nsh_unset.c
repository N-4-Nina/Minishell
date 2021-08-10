/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:15:48 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 15:15:49 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"

int	nsh_unset(t_sh *nsh, char **args)
{
	int		i;
	t_env	*node;

	i = 1;
	while (args[i])
	{
		node = NULL;
		node = find_by_name(nsh->env, args[i]);
		if (node)
			remove_var(nsh->env, node);
		i++;
	}
	return (0);
}

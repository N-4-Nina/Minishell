/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:09:43 by chpl              #+#    #+#             */
/*   Updated: 2021/08/11 18:17:42 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/builtins.h"

int	nsh_env(t_sh *nsh, char **args)
{
	t_env	*lst;

	args[0][0] = 'e';
	lst = nsh->env;
	while (lst)
	{
		write(1, lst->name, ft_strlen(lst->name));
		write(1, "=", 1);
		write(1, lst->value, ft_strlen(lst->value));
		write(1, "\n", 1);
		lst = lst->next;
	}
	*(nsh->last_status) = 0;
	return (0);
}

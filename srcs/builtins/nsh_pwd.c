/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:15:15 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 15:15:16 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"

int	nsh_pwd(t_sh *nsh, char **args)
{
	t_env	*var;

	args[0][0] = 'p';
	var = find_by_name(nsh->env, "PWD");
	write(1, var->value, ft_strlen(var->value));
	write(1, "\n", 1);
	*(nsh->last_status) = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:15:15 by chpl              #+#    #+#             */
/*   Updated: 2021/08/11 19:25:28 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/utils.h"

int	nsh_pwd(t_sh *nsh, char **args)
{
	char	*buf;

	args[0][0] = 'p';
	buf = get_current_dir_name();
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	*(nsh->last_status) = 0;
	free(buf);
	return (0);
}

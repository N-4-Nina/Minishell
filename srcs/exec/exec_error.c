/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:42:05 by chpl              #+#    #+#             */
/*   Updated: 2021/09/25 12:47:00 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"
#include "structures.h"
#include "utils.h"

void	exec_error(char *str, int *ret)
{
	if (!ft_strncmp(str, ".", 1))
	{
		*ret = 2;
		display_error("Nsh: .: \
filename argument required\n.: usage: . filename [arguments]\n", "", "");
	}
	else
	{
		display_error("Nsh:", strerror(errno), "\n");
		*ret = 126;
	}
}

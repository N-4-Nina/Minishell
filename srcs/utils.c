/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:21:06 by chpl              #+#    #+#             */
/*   Updated: 2020/11/24 10:26:24 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

char *get_current_dir_name(void)
{
	char	pwd[PATH_MAX];
	
	if (getcwd(pwd, sizeof(pwd)))
		return (ft_strdup(pwd));
	else
		return (NULL);
}


void    toggle(int i, t_trans *trs)
{
    if (trs->quotes[i] == 0)
        trs->quotes[i] = 1;
    else if (trs->quotes[i] == 1)
        trs->quotes[i] = 0;
	trs->skip = 1;
	trs->new = 1;
}

int		isBlank(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}
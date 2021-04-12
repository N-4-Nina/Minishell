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

int	isSpec(char c)
{
	return (c == '>' || c == '<' || 
		c == '|' || c == ';' ||
		c == '\\' || c == '$');
}
int	isQuote(char c)
{
    return (c == '\'' || c == '"');
}

int	isBlank(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}
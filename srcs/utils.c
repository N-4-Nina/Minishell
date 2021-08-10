/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:21:06 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 14:38:48 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libs.h"

void	free_array(char **ar, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(ar[i++]);
	if (ar)
		free(ar);
}

char	*get_current_dir_name(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)))
		return (ft_strdup(pwd));
	else
		return (NULL);
}

int	isSpec(char c)
{
	return (c == '>' || c == '<'
		|| c == '|' || c == ';');
}

int	isQuote(char c)
{
	return (c == '\'' || c == '"');
}

int	isBlank(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

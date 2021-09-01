/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:21:06 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 08:23:33 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libs.h"

int	display_error(char *one, char *two, char *three)
{
	if (one)
		write(STDERR_FILENO, one, ft_strlen(one));
	if (one)
		write(STDERR_FILENO, two, ft_strlen(two));
	if (one)
		write(STDERR_FILENO, three, ft_strlen(three));
	return (0);
}

char	*get_current_dir_name(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)))
		return (ft_strdup(pwd));
	else
		return (NULL);
}

int	is_spec(char c)
{
	return (c == '>' || c == '<'
		|| c == '|' || c == ';');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_blank(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

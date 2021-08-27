/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:21:06 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 15:22:49 by user42           ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:21:06 by chpl              #+#    #+#             */
/*   Updated: 2021/09/05 19:09:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libs.h"

int	display_error(char *one, char *two, char *three)
{
	char *str;
	char *tmp;
	
	str = NULL;
	if (one)
		str = ft_strdup(one);
	if (two)
	{
		tmp = str;
		str = ft_strjoin(str, two);
		free(tmp);
	}
	if (three)
	{
		tmp = str;
		str = ft_strjoin(str, three);
		free(tmp);
	}
	write(STDERR_FILENO, str, ft_strlen(str));
	if (str)
		free(str);
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

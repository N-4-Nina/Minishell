/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chappelle <chappelle@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:15:10 by chappelle         #+#    #+#             */
/*   Updated: 2021/08/09 13:21:25 by chappelle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

int	replace_status(char **dst, char *src, int status)
{
	char	*astat;

	(void)src;
	astat = ft_itoa(status);
	do_cat(dst, astat);
	free(astat);
	return (2);
}

int	replace_var(char **dst, char *src, t_env *env)
{
	t_env	*var;
	int		i;

	i = 1;
	while (src[i] && !(isBlank(src[i])) && src[i] != '"')
		i++;
	var = find_by_name(env, ft_substr(src, 1, i - 1));
	if (!var)
		return (i);
	do_cat(dst, var->value);
	return (i);
}

int	replace_strong(char **dst, char *src)
{
	int	i;

	i = 1;
	while (src[i] && src[i] != '\'')
		i++;
	do_cat(dst, ft_substr(src, 1, i - 1));
	return (i + 1);
}

int	replace_weak(char **dst, char *src, t_env *env)
{
	int		i;
	char	single[2];

	i = 1;
	single[1] = 0;
	while (src[i] && src[i] != '"')
	{
		if (src[i] == '$')
			i += replace_var(dst, &src[i], env);
		else
		{
			single[0] = src[i];
			do_cat(dst, &single[0]);
			i++;
		}
	}
	return (i + 1);
}

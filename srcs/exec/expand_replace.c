/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:15:10 by chappelle         #+#    #+#             */
/*   Updated: 2021/09/16 14:37:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "environment.h"
#include "utils.h"
#include "arrays.h"

int	replace_backslash(char **dst, char *src)
{
	do_cat(dst, src);
	free(src);
	return (2);
}

int	replace_status(char **dst, char *src, int status)
{
	char	*astat;

	(void)src;
	astat = ft_itoa(status);
	do_cat(dst, astat);
	free(astat);
	return (2);
}

int	replace_strong(char **dst, char *src)
{
	int		i;
	char	*sub;

	i = 1;
	while (src[i] && src[i] != '\'')
		i++;
	sub = ft_substr(src, 1, i - 1);
	do_cat(dst, sub);
	free(sub);
	return (i + 1);
}

int	replace_weak(char **dst, char *src, t_env *env, int *status)
{
	int		i;
	char	single[2];

	i = 1;
	single[1] = 0;
	while (src[i] && src[i] != '"')
	{
		if (src[i] == '$' && src[i + 1] == '?')
			i += replace_status(dst, &src[i], *status);
		else if (src[i] == '$')
			i += replace_var_in_quote(dst, &src[i], env);
		else if (src[i] == '\\' && src[i + 1])
			i += replace_backslash(dst, ft_substr(src, i + 1, 1));
		else
		{
			single[0] = src[i];
			do_cat(dst, &single[0]);
			i++;
		}
	}
	if (i == 1 && !*dst)
		*dst = ft_strdup("");
	return (i + 1);
}

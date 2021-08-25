/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:15:10 by chappelle         #+#    #+#             */
/*   Updated: 2021/08/25 16:19:57 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"
#include "../includes/environment.h"
#include "../includes/utils.h"

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
	char	*sub;
	int		i;

	if (ft_strlen(src) == 1)
	{
		do_cat(dst, src);
		return (1);	
	}
	else if (isQuote(src[1]) || isBlank(src[1]))
	{
		do_cat(dst, "$");
		return (1);
	}
	i = 1;
	while (src[i] && src[i] != '/' && !(isBlank(src[i])) && !isQuote(src[i]))
		i++;
	sub = ft_substr(src, 1, i - 1);
	var = find_by_name(env, sub);
	free(sub);
	if (!var)
		return (i);
	do_cat(dst, var->value);
	return (i);
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
		if (src[i] == '$')
			i += replace_var(dst, &src[i], env);
		else
		{
			single[0] = src[i];
			do_cat(dst, &single[0]);
			i++;
		}
	}
	if (i == 1)
		*dst = ft_strdup("");
	return (i + 1);
}

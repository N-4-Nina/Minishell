/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:15:10 by chappelle         #+#    #+#             */
/*   Updated: 2021/09/14 16:33:55 by chpl             ###   ########.fr       */
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

int	replace_var_in_quote(char **dst, char *src, t_env *env)
{
	t_env	*var;
	char	*sub;
	int		i;

	if (ft_strlen(src) == 1)
		return (do_cat(dst, src));
	else if (!ft_isalnum(src[1]) && src[1] != '_')
		return (do_cat(dst, "$"));
	i = 1;
	while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
		i++;
	sub = ft_substr(src, 1, i - 1);
	var = find_by_name(env, sub);
	free(sub);
	if (!var)
		do_cat(dst, "");
	else
		do_cat(dst, var->value);
	return (i);
}

void	replace_var_multi_args(char **dst, char *src, t_smpl *s)
{
	char	**split;
	int		i;

	split = ft_split(src, 32);
	i = 0;
	if (!split)
		return ;
	if (src[0] != 32 || !*dst)
		do_cat(dst, split[i++]);
	s->argc++;
	while (split[i])
		s->argv[s->argc++] = ft_strdup(split[i++]);
	free_array(split, i - 1);
	s->argc--;
}

int	replace_var(char **dst, char *src, t_env *env, t_smpl *s)
{
	t_env	*var;
	char	*sub;
	int		i;

	if (ft_strlen(src) == 1)
		return (do_cat(dst, src));
	else if (!ft_isalnum(src[1]) && src[1] != '_')
		return (do_cat(dst, "$"));
	i = 1;
	while (src[i] && (ft_isalnum(src[i]) || src[i] == '_'))
		i++;
	sub = ft_substr(src, 1, i - 1);
	var = find_by_name(env, sub);
	free(sub);
	if (!var)
		do_cat(dst, "");
	else if (!ft_strchr(var->value, 32))
		do_cat(dst, var->value);
	else
		replace_var_multi_args(dst, var->value, s);
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

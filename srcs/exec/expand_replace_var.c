/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:05:21 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 15:03:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "environment.h"
#include "arrays.h"

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

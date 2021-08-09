/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chappelle <chappelle@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:49:34 by chpl              #+#    #+#             */
/*   Updated: 2021/08/09 14:12:58 by chappelle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	do_cat(char **dst, char *src)
{
	int		len;
	char	*tmp;

	if (!*dst)
	{
		*dst = ft_strdup(src);
		return ;
	}
	len = ft_strlen(*dst) + ft_strlen(src) + 1;
	tmp = ft_strdup(*dst);
	free(*dst);
	*dst = malloc(len);
	ft_strlcpy(*dst, tmp, ft_strlen(tmp) + 1);
	ft_strlcat(*dst, src, len);
	free(tmp);
}

char	*expand_word(char *s, t_env *env, int *status)
{
	int		i;
	char	*new;
	char	single[2];

	i = 0;
	single[1] = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '\'')
			i += replace_strong(&new, &s[i]);
		else if (s[i] == '"')
			i += replace_weak(&new, &s[i], env);
		else if (s[i] == '$' && s[i + 1] == '?')
			i += replace_status(&new, &s[i], *status);
		else if (s[i] == '$')
			i += replace_var(&new, &s[i], env);
		else if (s[i] == '\\' && s[i + 1])
		{
			do_cat(&new, ft_substr(s, i + 1, 1));
			i += 2;
		}
		else
		{
			single[0] = s[i];
			do_cat(&new, &single[0]);
			i++;
		}
	}
	return (new);
}

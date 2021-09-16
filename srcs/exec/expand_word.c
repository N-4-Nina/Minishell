/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 14:49:34 by chpl              #+#    #+#             */
/*   Updated: 2021/09/16 14:03:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"

int	do_cat(char **dst, char *src)
{
	int		len;
	char	*tmp;

	if (!*dst)
	{
		*dst = ft_strdup(src);
		return (1);
	}
	len = ft_strlen(*dst) + ft_strlen(src) + 1;
	tmp = ft_strdup(*dst);
	free(*dst);
	*dst = malloc(len);
	ft_strlcpy(*dst, tmp, ft_strlen(tmp) + 1);
	ft_strlcat(*dst, src, len);
	free(tmp);
	return (1);
}

int	append_single(char **dst, char c)
{
	int		len;
	char	*tmp;
	char	src[2];

	src[0] = c;
	src[1] = 0;
	if (!*dst)
	{
		*dst = ft_strdup(src);
		return (1);
	}
	len = ft_strlen(*dst) + 2;
	tmp = ft_strdup(*dst);
	free(*dst);
	*dst = malloc(len);
	ft_strlcpy(*dst, tmp, ft_strlen(tmp) + 1);
	ft_strlcat(*dst, src, len);
	free(tmp);
	return (1);
}

char	*expand_word(char *s, t_env *env, int *status, t_smpl *smpl)
{
	int		i;
	char	**new;

	i = 0;
	while (s[i])
	{
		new = &smpl->argv[smpl->argc];
		if (s[i] == '\'')
			i += replace_strong(new, &s[i]);
		else if (s[i] == '"')
			i += replace_weak(new, &s[i], env, status);
		else if (s[i] == '$' && s[i + 1] == '?')
			i += replace_status(new, &s[i], *status);
		else if (s[i] == '$')
			i += replace_var(new, &s[i], env, smpl);
		else if (s[i] == '\\' && s[i + 1])
			i += replace_backslash(new, ft_substr(s, i + 1, 1));
		else
			i += append_single(new, s[i]);
	}
	return (*new);
}

char	*expand_io(char *s, t_env *env, int *status, t_smpl *smpl)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '\'')
			i += replace_strong(&new, &s[i]);
		else if (s[i] == '"')
			i += replace_weak(&new, &s[i], env, status);
		else if (s[i] == '$' && s[i + 1] == '?')
			i += replace_status(&new, &s[i], *status);
		else if (s[i] == '$')
			i += replace_var(&new, &s[i], env, smpl);
		else if (s[i] == '\\' && s[i + 1])
			i += replace_backslash(&new, ft_substr(s, i + 1, 1));
		else
			i += append_single(&new, s[i]);
	}
	return (new);
}

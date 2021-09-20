/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:38:18 by user42            #+#    #+#             */
/*   Updated: 2021/09/20 13:18:47 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "utils.h"
#include "environment.h"
#include "arrays.h"

int	set_abs_path(t_smpl *s, char *name)
{
	struct stat	buf;

	if (!stat(name, &buf))
	{
		s->path = ft_strdup(name);
		s->path_is_set = 1;
		return (1);
	}
	return (0);
}

int	seek_in_path(t_smpl *s, char **split, char *name, int splitSize)
{
	int			i;
	char		*path;
	struct stat	buf;

	i = 0;
	while (split[i])
	{
		if (split[i][ft_strlen(split[i]) - 1] == '/')
			split[i][ft_strlen(split[i]) - 1] = 0;
		path = ft_strjoin(split[i], name);
		if (!stat(path, &buf))
		{
			s->path = ft_strdup(path);
			free_array(split, splitSize);
			free(path);
			free(name);
			s->path_is_set = 1;
			return (1);
		}
		else
			free(path);
		i++;
	}
	return (0);
}

char	**get_split(t_env *env)
{
	t_env	*node;
	char	*str;
	char	**split;

	node = find_by_name(env, "PATH");
	if (!node)
		return (NULL);
	str = node->value;
	split = ft_split(str, ':');
	return (split);
}

int	set_cmd_path(t_smpl *s, t_env *env, char *name)
{
	int			j;
	char		*new;
	char		**split;

	j = 0;
	if (ft_strchr(name, '/'))
		return (set_abs_path(s, name));
	new = ft_strjoin("/", name);
	split = get_split(env);
	if (split)
	{
		while (split[j])
			j++;
		if (seek_in_path(s, split, new, j))
			return (1);
	}
	free_array(split, j);
	free(new);
	return (0);
}

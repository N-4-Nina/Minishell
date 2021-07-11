/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:38:18 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 17:59:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

int	set_abs_path(t_smpl *s, char *name)
{
	struct stat	buf;

	if (!stat(name, &buf))
	{
		s->path = ft_strdup(name);
		free(name);
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
			return (1);
		}
		else
			free(path);
		i++;
	}
	return (0);
}

int	set_cmd_path(t_smpl *s, t_env *env, char *name)
{
	int			j;
	char		**split;
	char		*new;

	j = 0;
	if (name[0] == '/')
		return (set_abs_path(s, name));
	new = ft_strjoin("/", name);
	free(name);
	name = new;
	split = ft_split(find_by_name(env, "PATH")->value, ':');
	while (split[j])
		j++;
	if (seek_in_path(s, split, name, j))
		return (1);
	free(name);
	free_array(split, j);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:07:09 by chpl              #+#    #+#             */
/*   Updated: 2021/08/30 15:36:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"

int	env_is_empty(t_env *env)
{
	return (env->name == NULL && env->value == NULL && env->next == NULL);
}

int	env_size(t_env *node)
{
	t_env	*origin;
	int		i;

	i = 0;
	origin = node;
	while (node)
	{
		i++;
		node = node->next;
	}
	node = origin;
	return (i);
}

int	strmatch(char *s1, char *s2)
{
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	if (ft_strlen(s2) > len)
		len = ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (1);
	return (0);
}

char	**env_to_array(t_env *env, int *size)
{
	char	**arr;
	int		i;
	t_env	*list;

	list = env;
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (env_size(list) + 1));
	while (list)
	{
		arr[i] = malloc(ft_strlen(list->name) + ft_strlen(list->value) + 2);
		ft_strlcpy(&arr[i][0], list->name, ft_strlen(list->name) + 1);
		arr[i][ft_strlen(list->name)] = '=';
		ft_strlcpy(&arr[i][ft_strlen(list->name) + 1], list->value, \
ft_strlen(list->value) + 1);
		i++;
		list = list->next;
	}
	*size = i;
	arr[i] = NULL;
	return (arr);
}

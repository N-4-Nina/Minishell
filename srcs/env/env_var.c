/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:36:02 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 12:03:45 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "environment.h"

void	remove_var(t_env **env, t_env *node)
{
	t_env	*lst;

	lst = *env;
	if (lst == node)
	{
		*env = lst->next;
		free(lst->name);
		free(lst->value);
		free(lst);
		return ;
	}
	while (lst->next != node)
		lst = lst->next;
	lst->next = node->next;
	free(node->name);
	free(node->value);
	free(node);
}

void	add_var(t_env *env, char *name, char *value)
{
	t_env	*list;
	t_env	*new;

	if (env_is_empty(env))
	{
		env->name = ft_strdup(name);
		env->value = ft_strdup(value);
		env->next = NULL;
	}
	else
	{
		new = (t_env *)malloc(sizeof(t_env));
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->next = NULL;
		list = env;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

t_env	*find_by_name(t_env *env, char *str)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (strmatch(str, current->name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

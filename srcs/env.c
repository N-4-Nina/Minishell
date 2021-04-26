/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:37:25 by chpl              #+#    #+#             */
/*   Updated: 2020/11/26 10:11:49 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	remove_var(t_env *env, t_env *node)
{
	t_env	*lst;

	lst = env;
	if (lst == node)
	{
		env = lst->next;
		free(lst->name);
		free(lst->value);
		free(lst);
		return;
	}
	while (lst->next != node)
		lst = lst->next;
	lst->next = node->next;
	free(node->name);
	free(node->value);
	free(node);
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

char	**env_to_array(t_env *env)
{
	char	**arr;
	int	i;
	int	j;
	t_env	*list;

	list = env;
	i = 0;
	arr = (char**)malloc(sizeof(char*));
	while (list)
	{
		j = 0;
		arr[i] = malloc(ft_strlen(list->name) + ft_strlen(list->value) +2);
		while(list->name[j])
		{
			arr[i][j] = list->name[j];
			j++;
		}
		arr[i][j] = '=';
		j = 0;
		while(list->value[j])
		{
			arr[i][j+1+ft_strlen(list->name)] = list->value[j];
			j++;
		}
		i++;
		list = list->next;
	}
	return (arr);
}

int		env_is_empty(t_env *env)
{
	return (env->name == NULL && env->value == NULL && env->next == NULL);
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
		new = (t_env*)malloc(sizeof(t_env));
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

void	env_clear(t_env *env)
{
	t_env	*current;
	t_env	*tmp;

	current = env;
	while (current)
	{
		tmp = current-> next;
		free(current->name);
		free(current->value);
		free(current);
		current = tmp;
	}
}
void	env_init(t_env **env)
{
	char	*cdn;

	*env = (t_env*)malloc(sizeof(t_env));
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->next = NULL;
	cdn = get_current_dir_name();
	add_var(*env, "PWD", cdn);
	free(cdn);
	add_var(*env, "PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/bin/");
	//add_var("USER", execve("/usr/bin/id", ["id", "-u", "-n"], NULL));

}


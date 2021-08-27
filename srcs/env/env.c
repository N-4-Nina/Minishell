/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:37:25 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 10:58:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/utils.h"
#include "../includes/arrays.h"

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

void	add_heredoc_path(t_env **env)
{
	char	*tmp;
	char	*str;

	tmp = getenv("USER");
	if (!tmp)
		tmp = ft_strdup("user42");
	add_var(*env, "USER", tmp);
	str = ft_strjoin("/home/", tmp);
	tmp = ft_strjoin(str, "/.nsh_heredoc");
	add_var(*env, "HEREDOC", tmp);
	free(str);
	free(tmp);
}

//init must be secured : should return something if a getenv returns NULL.
void	env_init(t_env **env, char **envp)
{
	char	*var;
	char	*val;
	int		i;
	int		envSize;

	*env = (t_env *)malloc(sizeof(t_env));
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->next = NULL;
	i = 0;
	envSize = array_size(envp);
	while (i < envSize)
	{
		val = ft_strchr(envp[i], '=') + 1;
		var = ft_substr(envp[i], 0, (int)(val - envp[i] - 1));
		add_var(*env, var, val);
		free(var);
		i++;
	}
	add_heredoc_path(env);
}

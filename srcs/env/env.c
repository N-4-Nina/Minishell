/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:37:25 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 08:24:56 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/utils.h"
#include "../includes/arrays.h"

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

void	env_init(t_env **env, char **envp)
{
	char	*var;
	char	*val;
	int		i;
	int		env_size;

	*env = (t_env *)malloc(sizeof(t_env));
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->next = NULL;
	i = 0;
	env_size = array_size(envp);
	while (i < env_size)
	{
		val = ft_strchr(envp[i], '=') + 1;
		var = ft_substr(envp[i], 0, (int)(val - envp[i] - 1));
		if (!ft_strncmp(var, "SHLVL", 6))
			update_shlvl(*env, var, val);
		else
			add_var(*env, var, val);
		free(var);
		i++;
	}
	if (!find_by_name(*env, "SHLVL"))
		add_var(*env, "SHLVL", "1");
	add_heredoc_path(env);
}

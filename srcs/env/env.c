/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:37:25 by chpl              #+#    #+#             */
/*   Updated: 2021/08/30 15:36:59 by user42           ###   ########.fr       */
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

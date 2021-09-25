/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_spec_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 14:02:21 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 12:06:39 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libs.h"
#include "structures.h"

void	add_heredoc_path(t_env **env)
{
	char	*tmp;
	char	*str;

	tmp = getenv("USER");
	if (!tmp)
		tmp = ft_strdup("user42");
	str = ft_strjoin("/home/", tmp);
	tmp = ft_strjoin(str, "/.nsh_heredoc");
	add_var(*env, "HEREDOC", tmp);
	free(str);
	free(tmp);
}

void	update_shlvl(t_env *env, char *var, char *lvl)
{
	int	n;

	n = ft_atoi(lvl);
	n++;
	lvl = ft_itoa(n);
	add_var(env, var, lvl);
	free(lvl);
	return ;
}

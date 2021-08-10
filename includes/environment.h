/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:58:28 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 11:58:29 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "nsh.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env	*find_by_name(t_env *env, char *str);
int		env_is_empty(t_env *env);
void	add_var(t_env *env, char *name, char *value);
void	env_clear(t_env *env);
void	remove_var(t_env *env, t_env *node);
char	**env_to_array(t_env *env, int *size);

#endif
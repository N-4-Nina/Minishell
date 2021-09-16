/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:40:10 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 15:07:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "environment.h"

void	count_ws_in_var(char *val, int *c)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == 32)
		{
			while (val[i] == 32)
				i++;
			if (val[i])
				(*c)++;
		}
		else
			i++;
	}
}

int	args_in_var(char *s, t_env *env, int *c)
{
	int		i;
	t_env	*var;
	char	*sub;

	i = 1;
	if (ft_strlen(s) == 1)
		return (1);
	else if (!ft_isalnum(s[1]) && s[1] != '_')
		return (1);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	i--;
	sub = ft_substr(s, 1, i);
	var = find_by_name(env, sub);
	free(sub);
	if (!var)
		return (i);
	else
	{
		count_ws_in_var(var->value, c);
		return (i);
	}
}

int	args_in_node(t_ast *node, t_env *env)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	c = 1;
	s = node->data;
	while (s[i])
	{
		if (s[i] == '$' && (i > 0 && s[i - 1] != '\\') && s[i + 1])
			i += args_in_var(&s[i], env, &c) + 1 ;
		else
			i++;
	}
	return (c);
}

int	args_count(t_ast *node, t_env *env)
{
	int	ac;

	ac = 0;
	while (node && (node->left->type == N_WORD
			|| node->left->type == N_IO_FILE || node->type == N_CMD_SUFFIX))
	{
		if (node->left->type != N_IO_FILE)
			ac += args_in_node(node->left, env);
		node = node->right;
	}
	return (ac);
}

void	files_count(t_ast *node, int *c)
{
	if (node->type == N_IO_FILE)
		(*c)++;
	if (node->right)
		files_count(node->right, c);
	if (node->left)
		files_count(node->left, c);
}

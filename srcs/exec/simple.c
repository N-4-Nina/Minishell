/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:10:02 by chpl              #+#    #+#             */
/*   Updated: 2021/09/14 17:10:22 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "environment.h"
#include "libs.h"
#include "exec.h"
#include "arrays.h"

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

void	init_simple(t_smpl *s, int fc)
{
	s->argv = (char **)malloc(sizeof(char *) * (s->ac_alloc + 1));
	ft_bzero(s->argv, sizeof(char *) * (s->ac_alloc + 1));
	s->files = (int *)malloc(sizeof(int *) * (fc + 1));
	ft_bzero(s->files, sizeof(int *) * (fc + 1));
	s->argc = 0;
	s->input = STDIN_FILENO;
	s->output = STDOUT_FILENO;
	s->filesnb = 0;
	s->has_cmd_word = 0;
	s->path_is_set = 0;
	s->isbuiltin = -1;
	s->path = NULL;
}

t_smpl	*abort_simple(t_smpl *s)
{
	if (s->path)
		free(s->path);
	//if (s->has_cmd_word)
	free_array(s->argv, s->ac_alloc);
	//if (s->argv)
	//	free(s->argv);
	if (s->files)
		free(s->files);
	free(s);
	return (NULL);
}

t_smpl	*build_simple(t_sh *nsh, t_ast *node)
{
	t_smpl	*s;
	int		fc;

	s = (t_smpl *)malloc(sizeof(t_smpl));
	fc = 0;
	s->ac_alloc = args_count(node, nsh->env);
	files_count(node, &fc);
	init_simple(s, fc);
	if (node->left->type == N_IO_FILE)
	{
		if (handle_io_first(s, node, nsh) == -1)
			return (abort_simple(s));
	}
	else
	{
		if (id_cmd_word(s, node, nsh) == -1)
			return (abort_simple(s));
	}
	s->argv[s->argc] = NULL;
	return (s);
}

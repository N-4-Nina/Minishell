/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:10:02 by chpl              #+#    #+#             */
/*   Updated: 2021/08/30 14:00:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"

int	args_count(t_ast *node)
{
	int	ac;

	ac = 0;
	while (node && (node->left->type == N_WORD
			|| node->left->type == N_IO_FILE || node->type == N_CMD_SUFFIX))
	{
		if (node->left->type != N_IO_FILE)
			ac++;
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

void	init_simple(t_smpl *s, int ac, int fc)
{
	s->argv = (char **)malloc(sizeof(char *) * (ac + 1));
	s->files = (int *)malloc(sizeof(int *) * (fc + 1));
	s->argc = 0;
	s->input = STDIN_FILENO;
	s->output = STDOUT_FILENO;
	s->filesnb = 0;
	s->has_cmd_word = 0;
	s->isbuiltin = -1;
	s->path = NULL;
}

t_smpl	*abort_simple(t_smpl *s)
{
	if (s->path)
		free(s->path);
	if (s->has_cmd_word)
		free(s->argv[0]);
	if (s->argv)
		free(s->argv);
	if (s->files)
		free(s->files);
	free(s);
	return (NULL);
}

t_smpl	*build_simple(t_sh *nsh, t_ast *node)
{
	t_smpl	*s;
	int		ac;
	int		fc;

	s = (t_smpl *)malloc(sizeof(t_smpl));
	fc = 0;
	ac = args_count(node);
	files_count(node, &fc);
	init_simple(s, ac, fc);
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

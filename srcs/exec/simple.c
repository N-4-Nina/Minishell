/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:10:02 by chpl              #+#    #+#             */
/*   Updated: 2021/09/16 15:00:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "environment.h"
#include "libs.h"
#include "exec.h"
#include "arrays.h"

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
	free_array(s->argv, s->ac_alloc);
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

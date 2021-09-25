/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:32:38 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 12:45:22 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "builtins.h"
#include "utils.h"

int	id_cmd_suffix(t_smpl *s, t_ast *node, t_sh *nsh)
{
	if (node->left->type == N_IO_FILE)
		return (handle_io_suf(s, node->left, nsh->env, nsh->last_status));
	else
		return (handle_word_suf(s, node->left, nsh->env, nsh->last_status));
}

int	validate_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh)
{
	s->has_cmd_word = 1;
	s->argc++;
	node = node->right;
	while (node)
	{
		if (id_cmd_suffix(s, node, nsh) == -1)
			return (-1);
		node = node->right;
	}
	return (1);
}

int	id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh)
{
	struct stat	buf;

	expand_word(node->left->data, nsh->env, nsh->last_status, s);
	s->isbuiltin = is_builtin(s->argv[0], nsh->bui);
	if (s->isbuiltin != -1)
		NULL;
	else if (!*s->argv[0])
		return (-1);
	else if (s->isbuiltin == -1 && !set_cmd_path(s, nsh->env, s->argv[0]))
	{
		*nsh->last_status = 127;
		return (validate_cmd_word(s, node, nsh));
	}
	if (s->isbuiltin == -1 && ft_strncmp(s->path, ".", 1)
		&& !stat(s->path, &buf) && S_ISDIR(buf.st_mode))
	{
		display_error("Nsh: ", s->path, " is a directory\n");
		*nsh->last_status = 126;
		return (-1);
	}
	return (validate_cmd_word(s, node, nsh));
}

int	handle_word_suf(t_smpl *s, t_ast *node, t_env *env, int *status)
{
	expand_word(node->data, env, status, s);
	if (!s->argv[s->argc])
		s->argv[s->argc] = ft_strdup("");
	s->argc++;
	return (1);
}

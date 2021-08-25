/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:32:38 by user42            #+#    #+#             */
/*   Updated: 2021/08/25 11:09:25 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"
#include "../includes/builtins.h"

int	id_cmd_suffix(t_smpl *s, t_ast *node, t_sh *nsh)
{
	if (node->left->type == N_IO_FILE)
		return (handle_io_suf(s, node->left, nsh->env, nsh->last_status));
	else
		return (handle_word_suf(s, node->left, nsh->env, nsh->last_status));
}

int	id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh)
{
	char	*xpd;

	xpd = expand_word(node->left->data, nsh->env, nsh->last_status);
	s->isbuiltin = is_builtin(xpd, nsh->bui);
	if (s->isbuiltin != -1)
		free(xpd);
	else if (!set_cmd_path(s, nsh->env, xpd))
	{
		*nsh->last_status = 127;
		return (-1);
	}
	s->argv[0] = ft_strdup(node->left->data);
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

int	handle_word_suf(t_smpl *s, t_ast *node, t_env *env, int *status)
{
	s->argv[s->argc] = expand_word(node->data, env, status);
	s->argc++;
	return (1);
}

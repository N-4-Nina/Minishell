/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:01:22 by chpl              #+#    #+#             */
/*   Updated: 2021/09/09 09:20:17 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "environment.h"
#include "utils.h"

int	check_heredoc_var(t_ast *node, t_env *env, char **hd)
{
	if (ft_strncmp(node->right->data, "<<", 3))
	{
		*hd = NULL;
		return (1);
	}
	else if (!find_by_name(env, "HEREDOC"))
	{
		display_error("Please set a valid HEREDOC variable.\n", "", "");
		return (0);
	}
	else
	{
		*hd = find_by_name(env, "HEREDOC")->value;
		return (1);
	}
}

int	handle_io_suf(t_smpl *s, t_ast *node, t_env *env, int *status)
{
	char	*hd;
	char	*xpd;

	hd = NULL;
	if (!check_heredoc_var(node, env, &hd))
		return (-1);
	if (ft_strncmp(node->right->data, "<<", 3))
		xpd = expand_io(node->left->data, env, status, s);
	else
		xpd = ft_strdup(node->left->data);
	open_file(s, xpd, hd, get_flags(node->right->data));
	free(xpd);
	if (s->output == -1)
	{
		*status = 1;
		return (-1);
	}
	return (1);
}

int	handle_node(t_smpl *s, t_ast *node, t_sh *nsh)
{
	int	check;

	check = 0;
	if (node->left->type == N_WORD && !s->has_cmd_word)
		check = id_cmd_word(s, node, nsh);
	else if (node->left->type == N_WORD)
		check = id_cmd_suffix(s, node, nsh);
	else if (node->left->type == N_IO_FILE)
		check = handle_io_suf(s, node->left, nsh->env, nsh->last_status);
	if (check < 0)
		return (-1);
	return (1);
}

int	handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh)
{
	t_ast	*io_node;
	char	*hd;
	char	*xpd;

	hd = NULL;
	io_node = node->left;
	if (!check_heredoc_var(io_node, nsh->env, &hd))
		return (-1);
	if (ft_strncmp(io_node->right->data, "<<", 3))
		xpd = expand_io(io_node->left->data, nsh->env, nsh->last_status, s);
	else
		xpd = ft_strdup(io_node->left->data);
	open_file(s, xpd, hd, get_flags(io_node->right->data));
	free(xpd);
	if (s->output == -1)
		return ((*nsh->last_status = 1) - 2);
	node = node->right;
	if (node)
	{
		if (handle_node(s, node, nsh) < 0)
			return (-1);
	}
	return (1);
}

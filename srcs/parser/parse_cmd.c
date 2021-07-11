/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                             :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:28:28 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	parse_simple_cmd(t_sh *nsh, t_ast **current)
{
	t_ast	*new;

	if (lex_isover(*nsh->lex))
		return (0);
	new = new_node(N_SIMPLE_CMD, ft_strdup("SIMPLE_CMD"));
	if (parse_io_file(nsh, &new->left))
	{
		graft_node_left(current, new);
		while (parse_cmd_suffix(nsh, current) && !lex_isover(*nsh->lex))
			current = &(*current)->right;
		return (1);
	}
	else if (parse_word(nsh, &new->left))
	{
		graft_node_left(current, new);
		while (parse_cmd_suffix(nsh, current) && !lex_isover(*nsh->lex))
			current = &(*current)->right;
		return (1);
	}
	free_node(new, 1);
	return (0);
}

int	add_pipe_seq(t_sh *nsh, t_ast **current, int dir)
{
	t_ast	*new;

	if (lex_isover(*nsh->lex))
		return (0);
	new = new_node(N_PIPE_SEQ, ft_strdup("PIPE"));
	if (parse_simple_cmd(nsh, &new->left))
	{
		if (dir == 0)
			graft_node_left(current, new);
		else
			graft_node_right(current, new);
		if ((lex_isover(*(nsh->lex)) \
		 || (nsh->lex->t[nsh->lex->i].type == SEMI)))
			return (2);
		else if (validate(nsh->lex, PIPE))
			return (1);
	}
	free_node(new, 1);
	return (0);
}

int	add_command(t_sh *nsh, t_ast **current)
{
	int	check;

	if (lex_isover(*nsh->lex))
		return (0);
	check = add_pipe_seq(nsh, current, 0);
	if (check)
	{
		current = &((*current)->left);
		while (check == 1)
		{
			check = add_pipe_seq(nsh, current, 1);
			current = &(*current)->right;
		}
		return (1);
	}
	return (0);
}

int	parse_cmd(t_sh *nsh)
{
	int		check;
	t_ast	*current;
	t_ast	*new;

	new = new_node(N_CMD, ft_strdup("COMMAND"));
	current = nsh->ast;
	check = add_command(nsh, &new);
	if (check)
	{
		graft_node_right(&current, new);
		current = current->right;
		while (check && (validate(nsh->lex, SEMI)))
		{
			new = new_node(N_CMD, ft_strdup("COMMAND"));
			check = add_command(nsh, &new);
			graft_node_right(&current, new);
			current = current->right;
		}
		return (1);
	}
	return (0);
}

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

int	parse_word(t_sh *nsh, t_ast **current)
{
	t_ast	*new;

	if (lex_isover(*nsh->lex))
		return (0);
	new = node_from_tok(nsh->lex->t[nsh->lex->i]);
	if (!validate(nsh->lex, WORD))
	{
		free_node(new, 0);
		return (0);
	}
	graft_node_left(current, new);
	return (1);
}

int	parse_io_file(t_sh *nsh, t_ast **current)
{
	t_ast	*new;
	t_ast	*io;

	if (lex_isover(*nsh->lex))
		return (0);
	io = new_node(N_IO_FILE, ft_strdup("IO_FILE"));
	if (tok_is_redir(nsh->lex->t[nsh->lex->i]))
	{
		new = node_from_tok(nsh->lex->t[nsh->lex->i]);
		nsh->lex->i++;
		if (parse_word(nsh, &io))
		{
			graft_node_left(current, io);
			graft_node_right(&io, new);
			return (1);
		}
		nsh->lex->i--;
	}
	free_node(io, 1);
	return (0);
}

int	parse_cmd_suffix(t_sh *nsh, t_ast **current)
{
	t_ast	*new;

	if (lex_isover(*nsh->lex))
		return (0);
	new = new_node(N_CMD_SUFFIX, ft_strdup("CMD_SUFFIX"));
	if (parse_word(nsh, &new))
	{
		graft_node_right(current, new);
		return (1);
	}
	else if (parse_io_file(nsh, &new))
	{
		graft_node_right(current, new);
		return (1);
	}
	free_node(new, 1);
	return (0);
}

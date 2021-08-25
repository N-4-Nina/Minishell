/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:04:44 by chpl              #+#    #+#             */
/*   Updated: 2021/08/25 13:57:16 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/astree.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"

/*Obviously we need to check the presence of
both the redirection operator and the file
name or here_doc end string. Then we graft
them on both side of the IO FILE node.
*/

int	tok_is_redir(t_tok tok)
{
	return (tok.type == DGREAT || tok.type == DLESS
		|| tok.type == GREAT || tok.type == LESS);
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
		nsh->lex->syntax_error = 1;
		free_node(new, 1);
	}
	free_node(io, 1);
	return (0);
}

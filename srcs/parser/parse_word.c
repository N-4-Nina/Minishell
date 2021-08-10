/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:09:45 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 14:58:55 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/astree.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"

/*Very simple as we should already
know if the token is a word or not
from lexer, we just have to check.
*/

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

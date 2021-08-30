/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:40:53 by chpl              #+#    #+#             */
/*   Updated: 2021/08/28 10:57:48 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/astree.h"
#include "../includes/parser.h"
#include "../includes/utils.h"
#include "../includes/lexer.h"

int	syntax_error(t_lex *l)
{
	static char	*spec[6] = {">>", ">", "<<", "<", "|", ";"};
	t_tok		near;

	near = l->t[l->i];
	if (!lex_inbound(*l))
		display_error("Syntax Error: unexpected token.\n", "", "");
	if (near.type == WORD)
		display_error("Syntax Error, unexpected token near ", near.data, "\n");
	else if (near.type >= 0 && near.type < 6)
		display_error("Syntax Error, unexpected token near \"",
			spec[near.type], "\" \n");
	l->syntax_error = 1;
	return (0);
}

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

int	validate(t_lex *l, t_ttype expected)
{
	if (l->i >= l->nt)
		return (0);
	if (l->t[l->i].type == expected)
		l->i++;
	else
		return (0);
	return (1);
}

int	tok_is_redir(t_tok tok)
{
	return (tok.type == DGREAT || tok.type == DLESS
		|| tok.type == GREAT || tok.type == LESS);
}

int	syntax_error(t_tok t)
{
	static char	*spec[6] = {">>", ">", "<<", "<", "|", ";"};

	if (t.type == WORD)
		printf("Syntax Error, unexpected token: %s \n", t.data);
	else
		printf("Syntax Error, unexpected token: \"%s\" \n", spec[t.type]);
	return (0);
}

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

int	parse(t_sh *nsh)
{
	int	check;

	if (!nsh->lex->nt)
		return (0);
	check = tree_init(nsh);
	check = parse_cmd(nsh);
	if (!lex_isover(*nsh->lex) && lex_inbound(*nsh->lex))
		return (syntax_error(nsh->lex->t[nsh->lex->i]));
	write_dot(&nsh->ast);
	return (check);
}

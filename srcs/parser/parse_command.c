/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:45:34 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 14:59:21 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/astree.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"

/*Grammatically speaking, a command is one or a
serie of pipe_sequence, so we need to check if
we can parse at least one, and then parse the
potential other ones in a loop.
*/

int	parse_command(t_sh *nsh, t_ast **current)
{
	int	check;

	if (lex_isover(*nsh->lex))
		return (0);
	check = parse_pipe_seq(nsh, current, 0);
	if (check)
	{
		current = &((*current)->left);
		while (check == 1)
		{
			check = parse_pipe_seq(nsh, current, 1);
			current = &(*current)->right;
		}
		return (1);
	}
	return (0);
}

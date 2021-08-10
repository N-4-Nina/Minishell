/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_seq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:51:29 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 10:59:42 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

/*the important part here is the return value:
a pipe sequence is actually not define by the 
presence of a pipe in a command -but rather
by containing at least a simple cmd-: this means
that you can kind of imagine a sort of implicit
last pipe to the standard output/specified io file.
That's why we return 1 or 2 to specify if this
pipe sequence is actually over or not.
*/

int	parse_pipe_seq(t_sh *nsh, t_ast **current, int dir)
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
		if ((lex_isover(*(nsh->lex))
				|| (nsh->lex->t[nsh->lex->i].type == SEMI)))
			return (2);
		else if (validate(nsh->lex, PIPE))
			return (1);
	}
	free_node(new, 1);
	return (0);
}

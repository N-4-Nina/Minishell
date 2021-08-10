/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:00:58 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 11:08:17 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

/*pretty straight-forward: grammar
specify a simple cmd can be an io file
so we check if we can parse one, else 
we attempt to parse an actual word.
in both cases we also keep parsing
everything after that is related to 
the simple command.-suffixes-*/

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

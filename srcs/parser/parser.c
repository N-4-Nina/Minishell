/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 11:08:41 by chpl             ###   ########.fr       */
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

int	parse_input(t_sh *nsh)
{
	int		check;
	t_ast	*current;
	t_ast	*new;

	new = new_node(N_CMD, ft_strdup("COMMAND"));
	current = nsh->ast;
	check = parse_command(nsh, &new);
	if (check)
	{
		graft_node_right(&current, new);
		current = current->right;
		while (check && (validate(nsh->lex, SEMI)))
		{
			new = new_node(N_CMD, ft_strdup("COMMAND"));
			check = parse_command(nsh, &new);
			graft_node_right(&current, new);
			current = current->right;
		}
		return (1);
	}
	return (0);
}

int	parse(t_sh *nsh)
{
	int	check;

	if (!nsh->lex->nt)
		return (0);
	check = tree_init(nsh);
	check = parse_input(nsh);
	if (!lex_isover(*nsh->lex) && lex_inbound(*nsh->lex))
	{
		return (syntax_error(nsh->lex->t[nsh->lex->i]));
		return (0);
	}
	return (check);
}

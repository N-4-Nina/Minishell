/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:12:50 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 14:57:59 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/astree.h"
#include "../includes/parser.h"

void	ast_reset(t_ast **node)
{
	if (!node || !*node)
		return ;
	if ((*node)->left)
		ast_reset(&(*node)->left);
	if ((*node)->right)
		ast_reset(&(*node)->right);
	free_node((*node), 1);
}

int	tree_init(t_sh *nsh)
{
	nsh->ast = new_node(N_PROGRAM, ft_strdup("Program"));
	if (!nsh->ast)
		return (0);
	return (1);
}

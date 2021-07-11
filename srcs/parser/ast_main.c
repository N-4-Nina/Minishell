/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:41:27 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 16:51:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

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

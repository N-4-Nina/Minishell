/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_graft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:51:05 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 16:52:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

void	graft_node_left(t_ast **node, t_ast *new)
{
	t_ast	*current;

	if (!node || !new)
		return ;
	if (!*node)
	{
		*node = new;
		return ;
	}
	current = *node;
	while (current->left)
	{
		*node = (*node)->left;
		printf("jumping to left node\n");
	}
	(*node)->left = new;
}

void	graft_node_right(t_ast **node, t_ast *new)
{
	t_ast	*current;

	if (!node || !new)
		return ;
	if (!*node)
	{
		*node = new;
		return ;
	}
	current = *node;
	while (current->right)
		*node = (*node)->right;
	(*node)->right = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_grafting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:17:10 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 15:54:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/utils.h"

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
	(*node)->right = new;
}

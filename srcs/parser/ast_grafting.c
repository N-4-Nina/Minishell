/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_grafting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:17:10 by chpl              #+#    #+#             */
/*   Updated: 2021/09/18 09:33:53 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/utils.h"

void	graft_node_left(t_ast **node, t_ast *new)
{
	if (!node || !new)
		return ;
	if (!*node)
	{
		*node = new;
		return ;
	}
	(*node)->left = new;
}

void	graft_node_right(t_ast **node, t_ast *new)
{
	if (!node || !new)
		return ;
	if (!*node)
	{
		*node = new;
		return ;
	}
	(*node)->right = new;
}

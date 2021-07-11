/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:50:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 18:54:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

t_ntype	convert_type(t_ttype type)
{
	if (type >= DGREAT && type <= LESS)
		return (N_RED);
	if (type == PIPE)
		return (N_PIPE_SEQ);
	if (type == SEMI)
		return (N_CMD);
	if (type == WORD)
		return (N_WORD);
	else
		return (N_WORD);
}

t_ast	*new_node(t_ntype type, char *data)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->data = data;
	new->type = type;
	if (data)
		new->len = ft_strlen(data);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*node_from_tok(t_tok tok)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->data = tok.data;
	new->len = tok.len;
	new->type = convert_type(tok.type);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	free_node(t_ast *node, int free_data)
{
	(void)free_data;
	// if (node->data && free_data)
	// 	free(node->data);
	// node->data = NULL;
	if (node)
		free(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:18:38 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 11:24:11 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nsh.h"

/*I got two functions for adding nodes
which is not great and not very logical.
The explanation is related to my write_graph
function which helped me visualize the tree.
*/

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
	if (node->data && free_data)
		free(node->data);
	if (node)
		free(node);
}

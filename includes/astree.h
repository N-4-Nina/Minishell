/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:43:52 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 15:43:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include "structures.h"
# include "defines.h"

t_ast	*new_node(t_ntype type, char *datas);
t_ast	*node_from_tok(t_tok tok);
void	free_node(t_ast *node, int free_data);
void	graft_node_left(t_ast **node, t_ast *new);
void	graft_node_right(t_ast **node, t_ast *new);
void	ast_reset(t_ast **node);
int		tree_init(t_sh *nsh);

#endif
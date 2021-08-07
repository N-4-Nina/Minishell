/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/08/07 18:11:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int     validate(t_lex *l, t_ttype expected)
{    
	if (l->i >= l->nt)
		return (0);
	if (l->t[l->i].type == expected)
		l->i++;
	else
		return (0);
	return (1);
}

int     tok_is_redir(t_tok tok)
{
	return (tok.type == DGREAT || tok.type == DLESS \
|| tok.type == GREAT || tok.type == LESS);
}

int     parse_word(t_sh *nsh, t_ast **current)
{
	t_ast   *new;

	if (lex_isover(*nsh->lex))
		return (0);
	new = node_from_tok(nsh->lex->t[nsh->lex->i]);
	if (!validate(nsh->lex, WORD))
	{
		free_node(new, 0);
		return (0);
	}
	graft_node_left(current, new);
	return (1);
}

int     parse_io_file(t_sh *nsh, t_ast **current)
{
	t_ast   *new;
	t_ast   *io;

	if (lex_isover(*nsh->lex))
		return (0);
	io = new_node(N_IO_FILE, ft_strdup("IO_FILE"));
	if (tok_is_redir(nsh->lex->t[nsh->lex->i]))
	{
		new = node_from_tok(nsh->lex->t[nsh->lex->i]);
		nsh->lex->i++;
		if (parse_word(nsh, &io))
		{
			graft_node_left(current, io);
			graft_node_right(&io, new);
			return (1);
		}      
		nsh->lex->i--;
	}
	free_node(io, 1);
	return (0);
}

int     parse_cmd_suffix(t_sh *nsh, t_ast **current)
{
	t_ast   *new;

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

int     parse_simple_cmd(t_sh *nsh, t_ast **current)
{
	t_ast   *new;

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
		// printf("grafted simple cmd\n");
		while (parse_cmd_suffix(nsh, current) && !lex_isover(*nsh->lex))
			current = &(*current)->right;
		return (1);
	}
	free_node(new, 1);
	return (0);
}

int     add_pipe_seq(t_sh *nsh, t_ast **current, int dir)
{
	t_ast *new;
	
	if (lex_isover(*nsh->lex))
		return (0);
	new = new_node(N_PIPE_SEQ, ft_strdup("PIPE"));
	if (parse_simple_cmd(nsh, &new->left))
	{
		if (dir == 0)
			graft_node_left(current, new);
		else
			graft_node_right(current, new);
		// printf("grafted pipe seq\n");
		// printf("i = %d, nt = %d\n", nsh->lex->i, nsh->lex->nt);
		if ((lex_isover(*(nsh->lex)) || (nsh->lex->t[nsh->lex->i].type == SEMI)))
			return (2);
		else if (validate(nsh->lex, PIPE))
			return (1);
	}
	free_node(new, 1);
	return (0);
}

int     add_command(t_sh *nsh, t_ast **current)
{
	int     check;
	
	if (lex_isover(*nsh->lex))
		return (0);
	check = add_pipe_seq(nsh, current, 0);
	if (check)
	{
		current = &((*current)->left);
		while (check == 1)
		{
			// printf("adding another pipe sequence \n");
			check = add_pipe_seq(nsh, current, 1);
			current = &(*current)->right;
		}
		return (1);
	}
	return (0);
 }

 int     parse_cmd(t_sh *nsh)
 {
	int    check;
	t_ast   *current;
	t_ast   *new;

	new = new_node(N_CMD, ft_strdup("COMMAND"));
	current = nsh->ast;
	check = add_command(nsh, &new);
	if (check)
	{
		graft_node_right(&current, new);
		current = current->right;
		while (check && (validate(nsh->lex, SEMI)))
		{
			// printf("adding another command \n");
			new = new_node(N_CMD, ft_strdup("COMMAND"));
			check = add_command(nsh, &new);
			graft_node_right(&current, new);
			current = current->right;
			//printf(" after add_cmd, current tok is %s. i = %d check = %d \n", nsh->lex->t[nsh->lex->i].data, nsh->lex->i, check);
		}
		return (1);
	}
	return (0);
}

int syntax_error(t_tok t)
{
	static char *spec[6] = { ">>", ">", "<<", "<", "|", ";"};

	if (t.type == WORD)
		printf("Syntax Error, unexpected token near %s \n", t.data);
	else if (t.type > -1 && t.type < 6)
		printf("Syntax Error, unexpected token near \"%s\" \n", spec[t.type]);
	return (0);
}

int parse(t_sh *nsh)
 {
	int check;

	if (!nsh->lex->nt)
		return (0);
	check = tree_init(nsh);
	check = parse_cmd(nsh);
	if (!lex_isover(*nsh->lex) && lex_inbound(*nsh->lex))
	{
		return (syntax_error(nsh->lex->t[nsh->lex->i]));
		//printf("i = %d,    nt = %d   \n", nsh->lex->i, nsh->lex->nt);
		//printf("Syntax Error, unexpected token: %s \n", nsh->lex->t[nsh->lex->i-1].data);
		return (0);
	}
	write_dot(&nsh->ast);
	return (check);
 }
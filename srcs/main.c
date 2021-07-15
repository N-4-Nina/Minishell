/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:28:28 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void print_tokens(t_lex *l)
{
	int i = 0;

	while (i < l->nt)
	{
		printf("tok: %s  type: %d\n", l->t[i].data, l->t[i].type);
		i++;
	}
}

void	nsh_clear(t_sh *nsh)
{
	free(nsh->lex);
	free(nsh->inp);
	free_array(nsh->bui->str, 7);
	free(nsh->bui);
	env_clear(nsh->env);
}

void	nsh_reset(t_sh *nsh)
{
	free(nsh->inp->prompt);
	ast_reset(&(nsh->ast));
	lex_reset(nsh->lex);
}
void	win_init(t_inp *inp)
{
	struct	winsize w;
	(void)inp;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	// inp->curY = 0;
	// inp->winX = w.ws_col;
	// inp->winY = w.ws_row;
	//printf("term dimension = %dx%d\n", inp->winX, inp->winY);
}

void inp_init(t_inp *inp)
{
	int	i;

	i = 0;
	(void)inp;
	// while (i < ARG_MAX)
	// 	inp->buf[i++] = 0;
	// inp->pos = 0;
	// inp->size = 0;
	// inp->cpy = NULL;
	// his_init(inp->his);
	win_init(inp);
}

void	nsh_alloc(t_sh *nsh)
{
	nsh->lex = (t_lex *)malloc(sizeof(t_lex));
	nsh->inp = (t_inp *)malloc(sizeof(t_inp));
	nsh->bui = (t_bui *)malloc(sizeof(t_bui));
	nsh->last_status = (int *)malloc(sizeof(int));
}

int	nsh_init(t_sh *nsh)
{
	nsh_alloc(nsh);
	env_init(&nsh->env);
	lex_init(nsh->lex);
	inp_init(nsh->inp);
	bui_init(nsh);
	term_init(nsh->term);
	
	return (1);
}

int	main(void)
{
	t_sh	nsh;

	nsh_init(&nsh);
	nsh_loop(&nsh);
	return (0);
}

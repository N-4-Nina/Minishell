/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/08/07 14:13:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	print_tokens(t_lex *l)
{
	int	i;

	i = 0;
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

void	reset_sig_catcher(void)
{
	g_sig_catcher[0] = 0;
	g_sig_catcher[1] = 0;
}

int	main(void)
{
	t_sh	nsh;

	nsh_init(&nsh);
	nsh_loop(&nsh);
	return (0);
}

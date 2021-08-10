/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:10:45 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 18:18:53 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/lexer.h"
#include "../includes/astree.h"
#include "../includes/exec.h"
#include "../includes/utils.h"
#include "../includes/environment.h"

void	free_everything(t_sh *nsh)
{
	cmd_reset((t_cmd *)nsh->cmd);
	free_array(nsh->bui->str, 7);
	ast_reset(&nsh->ast);
	free(nsh->inp->prompt);
	free(nsh->inp->line);
	lex_reset(nsh->lex);
	free(nsh->lex);
	free(nsh->inp);
	free(nsh->bui);
	env_clear(nsh->env);
}

int	nsh_exit(t_sh *nsh, char **args)
{
	int	exit_status;

	free_everything(nsh);
	if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = *nsh->last_status;
	free(nsh->last_status);
	exit(exit_status);
}

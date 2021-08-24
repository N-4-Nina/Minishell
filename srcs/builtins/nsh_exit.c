/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:10:45 by chpl              #+#    #+#             */
/*   Updated: 2021/08/22 14:16:16 by chpl             ###   ########.fr       */
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
	if (nsh->inp->line)
		free(nsh->inp->line);
	lex_reset(nsh->lex);
	free(nsh->lex);
	free(nsh->inp);
	free(nsh->bui);
	free(nsh->last_status);
	env_clear(nsh->env);
}

int	handle_args(t_sh *nsh, char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i++]))
			{
				printf("Nsh: exit: %s: numeric argument required\n", args[1]);
				*nsh->last_status = 2;
				return (-1);
			}
		}
	}
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("Nsh: exit: too many arguments\n");
		*nsh->last_status = 1;
		return (0);
	}
	return (1);
}

int	nsh_exit(t_sh *nsh, char **args)
{
	int	exit_status;

	exit_status = handle_args(nsh, args);
	if (!exit_status)
		return (1);
	if (args[1] && exit_status > 0)
		exit_status = ft_atoi(args[1]);
	else
		exit_status = *nsh->last_status;
	free_everything(nsh);
	exit(exit_status);
}

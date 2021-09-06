/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:01:16 by chpl              #+#    #+#             */
/*   Updated: 2021/09/06 10:43:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "utils.h"
#include "arrays.h"

int	cmd_execute(t_sh *nsh, t_cmd *cmd)
{
	if (cmd->smpnb == 0)
		return (0);
	if (cmd->smpnb == 1)
		exec_single(nsh, cmd->smpl[0]);
	else
		exec_pipe_seq(nsh, cmd);
	return (0);
}

void	count_smpls(t_ast *node, t_cmd *cmd)
{
	t_ast	*pipenode;
	int		i;

	pipenode = node;
	cmd->smpnb = 0;
	i = 0;
	while (pipenode)
	{
		pipenode = pipenode->right;
		i++;
	}
	cmd->smpl = (t_smpl **)malloc(sizeof(t_smpl *) * i);
}

int	cmd_build(t_sh *nsh, t_ast *node, t_cmd *cmd)
{
	t_ast	*pipenode;

	pipenode = node;
	count_smpls(node, cmd);
	while (pipenode)
	{
		node = pipenode;
		while (node->type != N_SIMPLE_CMD)
			node = node->left;
		cmd->smpl[cmd->smpnb] = build_simple(nsh, node);
		if (cmd->smpl[cmd->smpnb] == NULL)
		{
			cmd_reset(cmd);
			return (-1);
		}
		pipenode = pipenode->right;
		cmd->smpnb++;
	}
	return (0);
}

void	cmd_reset(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->smpnb)
	{
		close_files(cmd->smpl[i]);
		free_array(cmd->smpl[i]->argv, cmd->smpl[i]->argc);
		if (cmd->smpl[i]->path)
			free(cmd->smpl[i]->path);
		if (cmd->smpl[i])
			free(cmd->smpl[i]);
		i++;
	}
	free(cmd->smpl);
}

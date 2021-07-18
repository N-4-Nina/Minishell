#include "../../includes/nsh.h"

int cmd_execute(t_sh *nsh, t_cmd *cmd)
{
	if (cmd->smpnb == 0)
		return(0);
	if (cmd->smpnb == 1)
		exec_single(nsh, cmd->smpl[0]);
	else
		exec_pipe_seq(nsh, cmd);
	return (0);
}

int cmd_build(t_sh *nsh, t_ast *node, t_cmd *cmd)
{
	t_ast   *pipenode;

	pipenode = node;
	cmd->smpnb = 0;
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

void    cmd_reset(t_cmd *cmd)
{
	int i;

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
}
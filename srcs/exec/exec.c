/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:00:33 by chpl              #+#    #+#             */
/*   Updated: 2021/08/30 16:57:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"
#include "../includes/environment.h"
#include "../includes/utils.h"
#include "../includes/signals.h"
#include "../includes/defines.h"
#include "../includes/arrays.h"

int	single_child(t_smpl *smpl, t_env *env)
{
	char	**envArr;
	int		envSize;
	int		error;

	envSize = 0;
	error = 0;
	signal(SIGINT, SIG_DFL);
	envArr = env_to_array(env, &envSize);
	if (execve(smpl->path, smpl->argv, envArr) == -1)
	{
		display_error(strerror(errno), "", "");
		error = 126;
	}
	free_array(envArr, envSize);
	exit(EXIT_SUCCESS + error);
}

int	fork_single(t_smpl *smpl, t_env *env, int *status)
{
	pid_t	pid;

	set_sig_behav(CATCH);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		single_child(smpl, env);
	else
		await_child(status);
	return (*status);
}

int	exec_single(t_sh *nsh, t_smpl *s)
{
	int	ret;
	int	origin[2];

	ret = 0;
	redirect(s, &origin[0], &origin[1]);
	if (s->has_cmd_word)
	{
		if (s->isbuiltin == -1)
			ret = fork_single(s, nsh->env, nsh->last_status);
		else
			ret = (call_builtin(nsh, s));
	}
	recover_origin(origin);
	return (ret);
}

int	build_exec(t_sh *nsh, t_ast *node)
{
	t_cmd	cmd;

	nsh->cmd = &cmd;
	while (node)
	{
		if (cmd_build(nsh, node->left, &cmd) == -1)
		{
			node = node->right;
			continue ;
		}
		cmd_execute(nsh, &cmd);
		cmd_reset(&cmd);
		node = node->right;
	}
	return (0);
}

int	exec(t_sh *nsh)
{
	build_exec(nsh, nsh->ast->right);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:00:33 by chpl              #+#    #+#             */
/*   Updated: 2021/09/14 16:35:57 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "environment.h"
#include "utils.h"
#include "signals.h"
#include "defines.h"
#include "arrays.h"

int	single_child(t_smpl *smpl, t_env *env)
{
	char	**env_arr;
	int		env_size;
	int		ret;

	env_size = 0;
	ret = 0;
	signal(SIGINT, SIG_DFL);
	env_arr = env_to_array(env, &env_size);
	if (smpl->path_is_set)
	{
		if (execve(smpl->path, smpl->argv, env_arr) == -1)
		{
			display_error("Nsh:", strerror(errno), "\n");
			ret = 126;
		}
	}
	else
	{
		display_error("Nsh: Command not found: ", smpl->argv[0], "\n");
		ret = 127;
	}
	free_array(env_arr, env_size);
	exit(EXIT_SUCCESS + ret);
}

int	fork_single(t_smpl *smpl, t_env *env, int *status)
{
	pid_t	pid;

	set_sig_behav(CATCH, smpl->argv[0]);
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
	if (s->input > 1)
		close(s->input);
	if (s->output > 1)
		close(s->output);
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

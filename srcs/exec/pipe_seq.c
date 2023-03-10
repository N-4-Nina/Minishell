/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:17:22 by chpl              #+#    #+#             */
/*   Updated: 2021/09/25 12:42:52 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"
#include "environment.h"
#include "signals.h"
#include "defines.h"
#include "utils.h"
#include "arrays.h"

void	pipe_seq_redir(t_smpl *s)
{
	if (s->input != -1 && s->input != STDIN_FILENO)
		dup2(s->input, STDIN_FILENO);
	if (s->output != -1 && s->output != STDOUT_FILENO)
		dup2(s->output, STDOUT_FILENO);
}

int	exec_seq_part(t_sh *nsh, t_smpl *s)
{
	char	**env_arr;
	int		env_size;
	int		ret;

	ret = 0;
	env_arr = env_to_array(nsh->env, &env_size);
	pipe_seq_redir(s);
	if (s->isbuiltin >= 0)
		ret = call_builtin(nsh, s);
	else if (s->path_is_set)
	{
		if (execve(s->path, s->argv, env_arr) == -1)
			exec_error(s->path, &ret);
	}
	else
	{
		display_error("Nsh: Command not found: ", s->argv[0], "\n");
		ret = 127;
	}
	free_array(env_arr, env_size);
	exit(EXIT_SUCCESS + ret);
}

void	pipe_seq_parent(t_sh *nsh, pid_t pid, int red[2], int *fd)
{
	close(red[1]);
	(void)nsh;
	(void)pid;
	if (*fd)
		close(*fd);
	*fd = red[0];
}

void	pipe_seq_child(t_sh *nsh, t_cmd *cmd, int red[2], int fd)
{
	close(red[0]);
	set_sig_behav(RESET, NULL);
	dup2(fd, STDIN_FILENO);
	if (fd)
		close(fd);
	if (cmd->i < cmd->smpnb - 1)
		dup2(red[1], STDOUT_FILENO);
	close(red[1]);
	exec_seq_part(nsh, cmd->smpl[cmd->i]);
}

int	exec_pipe_seq(t_sh *nsh, t_cmd *cmd)
{
	int		red[2];
	int		fd;
	pid_t	pid;

	cmd->i = 0;
	red[0] = 0;
	red[1] = 1;
	fd = 0;
	set_sig_behav(CATCH, NULL);
	while (cmd->i < cmd->smpnb)
	{
		if (pipe(red))
			write(2, "pipe creation error\n", 20);
		pid = fork();
		if (pid < 0)
			return (-1);
		if (!pid)
			pipe_seq_child(nsh, cmd, red, fd);
		else
			pipe_seq_parent(nsh, pid, red, &fd);
		cmd->i++;
	}
	if (fd > 1)
		close(fd);
	return (await_children(nsh, cmd));
}

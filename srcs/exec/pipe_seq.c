/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:17:22 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 08:24:56 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"
#include "../includes/environment.h"
#include "../includes/signals.h"
#include "../includes/defines.h"
#include "../includes/utils.h"
#include "../includes/arrays.h"

void	pipe_seq_redir(t_smpl *s)
{
	if (s->input != -1 && s->input != STDIN_FILENO)
		dup2(s->input, STDIN_FILENO);
	if (s->output != -1 && s->output != STDOUT_FILENO)
		dup2(s->output, STDOUT_FILENO);
}

int	exec_seq_part(t_sh *nsh, t_smpl *s, int red[2], int fd)
{
	char	**env_arr;
	int		env_size;
	int		error;

	error = 0;
	env_arr = env_to_array(nsh->env, &env_size);
	pipe_seq_redir(s);
	if (s->isbuiltin >= 0)
		call_builtin(nsh, s);
	else
	{
		if (execve(s->path, s->argv, env_arr) == -1)
		{
			display_error(strerror(errno), "\n", "");
			error = 126;
		}
	}
	dup2(fd, STDIN_FILENO);
	dup2(red[1], STDOUT_FILENO);
	free_array(env_arr, env_size);
	exit(EXIT_SUCCESS + error);
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
		dup2(red[1], 1);
	close(red[1]);
	exec_seq_part(nsh, cmd->smpl[cmd->i], red, fd);
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
			write(1, "pipe creation error\n", 20);
		pid = fork();
		if (pid < 0)
			return (-1);
		if (!pid)
			pipe_seq_child(nsh, cmd, red, fd);
		else
			pipe_seq_parent(nsh, pid, red, &fd);
		cmd->i++;
	}
	await_children(nsh, cmd);
	return (0);
}

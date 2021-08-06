#include "../../includes/nsh.h"

int exec_seq_part(t_sh *nsh, t_smpl *s, int red[2], int fd)
{
	char    **envArr;
	int     envSize;
	int		error;

	error = 0;
	envArr = env_to_array(nsh->env, &envSize);
	if (s->input != -1 && s->input != STDIN_FILENO)
		dup2(s->input, STDIN_FILENO);
	if (s->output != -1 && s->output != STDOUT_FILENO)
		dup2(s->output, STDOUT_FILENO);
	if (s->isbuiltin >= 0)
		call_builtin(nsh, s);
	else
		if (execve(s->path, s->argv, envArr) == -1)
			if (errno == EACCES)
			{
				printf("nsh: %s: Permission non accordée\n", s->path);
				error = 126;
			}
	dup2(fd, STDIN_FILENO);
	dup2(red[1], STDOUT_FILENO);
	free_array(envArr, envSize);
	exit(EXIT_SUCCESS + error);
}

int exec_pipe_seq(t_sh *nsh, t_cmd *cmd)
{
	int     i;
	int     red[2];
	int     fd;
	pid_t   pid;
	pid_t	wpid;

	i = 0;
	red[0] = 0;
	red[1] = 1;
	fd = 0;
	while (i < cmd->smpnb)
	{
		if (pipe(red))
			write(1, "pipe creation error\n", 20);
		pid = fork();
		if (pid < 0)
			return (-1);
		if (!pid)
		{
			close(red[0]);
			set_sig_behav(RESET);
			dup2(fd, 0);
			if (i < cmd->smpnb - 1)
				dup2(red[1], 1);
			exec_seq_part(nsh, cmd->smpl[i], red, fd);
		}
		else
		{
			close(red[1]);
			set_sig_behav(CATCH);
			wpid = waitpid(pid, nsh->last_status, WUNTRACED);
			*nsh->last_status = *nsh->last_status >> 8;
			//while (!WIFEXITED(*nsh->last_status) && !WIFSIGNALED(*nsh->last_status))
			//    wpid = waitpid(pid, nsh->last_status, WUNTRACED);
			fd = red[0];
		}
		i++;
	} 
	return (0);
}
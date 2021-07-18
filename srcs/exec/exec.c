#include "../../includes/nsh.h"

int	single_child(t_smpl *smpl, t_env *env)
{
	char	**envArr;
	int		envSize;

	envSize = 0;
	signal(SIGINT, SIG_DFL);
	envArr = env_to_array(env, &envSize);
	if (execve(smpl->path, smpl->argv, envArr) == -1)
		NULL;
	free_array(envArr, envSize);
	exit(EXIT_SUCCESS);
}

int	fork_single(t_smpl *smpl, t_env *env, int *status)
{
	pid_t	pid;
	pid_t	wpid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		single_child(smpl, env);
	else
	{
		signal(SIGINT, SIG_IGN);
		wpid = waitpid(pid, status, WUNTRACED);
		while (!WIFEXITED(*status) && !WIFSIGNALED(*status))
			wpid = waitpid(pid, status, WUNTRACED);
		*status = *status >> 8;
	}
	return (*status);
}

int exec_single(t_sh *nsh, t_smpl *s)
{
	int ret;
	int origin[2];

	ret = 0;
	redirect(s, &origin[0], &origin[1]);
	if (s->isbuiltin == -1)
		ret = fork_single(s, nsh->env, nsh->last_status);
	else
		ret = (call_builtin(nsh, s));
	recover_origin(origin);
	return (ret);
}

int call_builtin(t_sh *nsh, t_smpl *s)
{
	return (nsh->bui->func[s->isbuiltin](nsh, s->argv));
}

int build_exec(t_sh *nsh, t_ast *node)
{
	t_cmd   cmd;

	while (node)
	{
		if (cmd_build(nsh, node->left, &cmd) == -1)
		{
			node = node->right;
			continue;
		}
		cmd_execute(nsh, &cmd);
		cmd_reset(&cmd);
		node = node->right;
	}
	return (0);
}

int exec(t_sh *nsh)
{
	build_exec(nsh, nsh->ast->right);
	return (0);
}
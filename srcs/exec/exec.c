#include "../../includes/nsh.h"

int spawn(t_smpl *smpl, t_env *env)
{
    pid_t   pid;
    pid_t   wpid;
    char    **envArr;
    int     status;
    int     envSize;

    pid = fork();
    if (pid == -1)
		return (-1);
    if (pid == 0)
	{
        signal(SIGINT, SIG_DFL);
        envArr = env_to_array(env, &envSize);
		if (execve(smpl->path, smpl->argv, envArr) == -1)
            NULL;
			//printf("couldn't exec%s\n", smpl->path);
		free_array(envArr, envSize);
		exit(EXIT_SUCCESS);
	}
	else
	{
        signal(SIGINT, SIG_IGN);
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
    return (status);
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
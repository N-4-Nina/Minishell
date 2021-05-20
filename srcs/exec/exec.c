#include "../../includes/nsh.h"

int spawn(t_smpl *smpl, t_env *env)
{
    pid_t   pid;
    pid_t   wpid;
    char    **envArr;
    int     status;

    pid = fork();
    if (pid == -1)
		return(-1);
    if (pid == 0)
	{
        
        envArr = env_to_array(env);
		if (execve(smpl->path, smpl->argv, envArr) == -1)
			printf("couldn't exec%s\n", smpl->path);
		free_array(envArr);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
    return (status);
}

int call_builtin(t_sh *nsh, t_smpl *s)
{
    //printf("builtin number= %d, ret =%d\n", s->isbuiltin, nsh->bui->func[s->isbuiltin](nsh, s->argv));
    nsh->bui->func[s->isbuiltin](nsh, s->argv);
    return (1);
    //return(nsh->bui->func[s->isbuiltin](nsh, s->argv));
}

int build_exec(t_sh *nsh, t_ast *node)
{
    t_cmd   cmd;

    while (node)
    {
        cmd_build(nsh, node->left, &cmd);
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
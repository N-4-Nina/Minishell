#include "../includes/nsh.h"

int spawn(t_smpl smpl)
{
    t_pid pid;

    pid = fork();
    if (pid == -1)
		return(-1);
    if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		//	write(1, "couldn't exec, looking in PATH...\n", 25);
		path = ft_strjoin(find_by_name("PATH")->value, args[0]);
		if (execve(path, args, env) == -1)
		//	write(1, "couldn't find in path either\n", 20);
		free(path);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
}

int cmd_execute(t_cmd cmd)
{

}

int set_cmd_path(t_smpl *s, t_env *env, char *name)
{
    int     i;
    char    **split;
    char    *path;
    struct  stat    buf;

    i = 0;
    name = ft_strjoin("/", name);
    split = ft_split(find_by_name(env, "PATH")->value, ':');
    while (split[i])
    {
        path = ft_strjoin(split[i], name);
        if (!stat(path, &buf))
        {
            s->path = ft_strdup(path);
            i = 0;
            while (split[i])
                free(split[i++]);
            free(split);
            free(path);
    }
    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
    free(path);
    return (0);
}

void    handle_io(t_smpl *s, t_ast *node)
{
    
}
t_smpl build_simple(t_sh *nsh, t_ast *node)
{
    t_smpl s;

    if (node->type == N_IO_FILE)
        handle_io(&s, node);
    else
        identify_command_word();
    if ((s.isbuiltin = is_builtin(node->data) == -1)
        if (!set_cmd_path(&s, env, ))

}
int cmd_build(t_sh *nsh, t_ast *node)
{
    node = node->left;
    while (node)
    {
        build_simple(node);
        node = node->right;
    }
}

int build_exec(t_sh *nsh)
{
    t_ast *cmd;

    cmd = ast->right;
    while (cmd)
    {
        cmd_build(nsh, cmd);
        cmd_execute(nsh);
        cmd_reset(nsh->)

        cmd->right;
    }

}
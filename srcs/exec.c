#include "../includes/nsh.h"

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

int cmd_execute_pipe_seq(t_sh *nsh, t_cmd *cmd)
{
        // int     origin[2];
    // int     red[2];
    // int     i;

    // i = 0;
    // while (i < cmd->smpnb)
    // {

    //     i++;
    // }
    (void)nsh;
    (void)cmd;
    return (0);
}
int call_builtin(t_sh *nsh, t_smpl *s)
{
    //printf("builtin number= %d, ret =%d\n", s->isbuiltin, nsh->bui->func[s->isbuiltin](nsh, s->argv));
    nsh->bui->func[s->isbuiltin](nsh, s->argv);
    return (1);
    //return(nsh->bui->func[s->isbuiltin](nsh, s->argv));
}
int cmd_execute_single(t_sh *nsh, t_cmd *cmd)
{
    int ret;

    dup2(cmd->smpl[0]->input, 1);
    dup2(cmd->smpl[0]->output, 0);
    if (cmd->smpl[0]->isbuiltin == -1)
        ret = spawn(cmd->smpl[0], nsh->env);
    else
        ret = (call_builtin(nsh, cmd->smpl[0]));
    dup2(1, cmd->smpl[0]->input);
    dup2(0, cmd->smpl[0]->output);
    return (ret);
}

int cmd_execute(t_sh *nsh, t_cmd *cmd)
{
    if (cmd->smpnb == 0)
        return(0);
    if (cmd->smpnb == 1)
        cmd_execute_single(nsh, cmd);
    else
        cmd_execute_pipe_seq(nsh, cmd);
    (void)nsh;
    return (0);
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
        if (split[i][ft_strlen(split[i])-1] == '/')
            split[i][ft_strlen(split[i])-1] = 0;
        path = ft_strjoin(split[i], name);        
        if (!stat(path, &buf))
        {
            s->path = ft_strdup(path);
            printf("%s\n", s->path);
            free_array(split);
            free(path);
            return(1);
        }
        i++;
    }
    free_array(split);
    free(path);
    return (0);
}

int     get_flags(char *red)
{
    if (ft_strlen(red) == 2)
        return(FLAGS_DGREAT);
    else if (red[0] == '>')
        return(FLAGS_GREAT);
    else
        return(FLAGS_LESS);
}

int     open_file(t_smpl *s, char *file, int flags)
{
    int fd;

    fd = open(file, flags);
    if (fd > -1)
    {
        s->files[s->filesnb] = (int)malloc(sizeof(int));
        s->files[s->filesnb] = fd;
        s->filesnb++;
    }
    return(fd);
}


void    handle_word_suf(t_smpl *s, t_ast *node)
{
    s->argc++;
    s->argv[s->argc] = ft_strdup(node->data);
}

void    handle_io_suf(t_smpl *s, t_ast *node)
{
    if (node->left->data[0] == '>')
        s->output = open_file(s, node->left->data, get_flags(node->right->data));
    else
        s->input = open_file(s, node->left->data, get_flags(node->right->data));
}

void    id_cmd_suffix(t_smpl *s, t_ast *node)
{
    if (node->left->type == N_IO_FILE)
        handle_io_suf(s, node->left);
    else
        handle_word_suf(s, node->left);
}

void    id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh)
{
    if ((s->isbuiltin = is_builtin(node->left->data, nsh->bui)) != -1)
        (void)nsh;
    else if (!set_cmd_path(s, nsh->env, node->left->data))
        printf("Command not found: %s\n", node->left->data);
    s->argv[0] = ft_strdup(node->left->data);
    node = node->right;
    while (node)
    {
        
        id_cmd_suffix(s, node);
        node = node->right;
    }
}

void    handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh)
{
    t_ast *io_node;

    io_node = node;
    s->output = open_file(s, io_node->left->data, get_flags(io_node->right->data));
    if (node->right)
    {
        node = node->right;
        id_cmd_word(s, node, nsh);
    }    
}
void    init_simple(t_smpl *s)
{
    
    s->argv = (char **)malloc(sizeof(char*));
    s->files = (int*)malloc(sizeof(int*));
    s->argc = 0;
    s->input = 0;
    s->output = 1;
    s->filesnb = 0;
    s->isbuiltin = -1;
    s->name = NULL;
    s->path = NULL;
}
t_smpl *build_simple(t_sh *nsh, t_ast *node)
{
    t_smpl *s;

    s = (t_smpl*)malloc(sizeof(t_smpl));
    init_simple(s);
    if (node->left->type == N_IO_FILE)
        handle_io_first(s, node->left, nsh);
    else
        id_cmd_word(s, node, nsh);
    s->argv[s->argc + 1] = NULL;
    return (s);

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
        pipenode = pipenode->right;
        cmd->smpnb++;
    }
    return (0);
}

void    close_files(t_smpl *s)
{
    while (s->filesnb > 0)
    {
        s->filesnb--;
        printf("closing %d\n", s->files[s->filesnb]);
        printf("ret = %d\n", close(s->files[s->filesnb]));
        free(&s->files[s->filesnb]); 
    }

}
void    cmd_reset(t_cmd *cmd)
{
    int i;

    i = 0;
    while (i < cmd->smpnb)
    {
        printf("reset\n");
        close_files(cmd->smpl[i]);
        //free_array(cmd->smpl[i]->argv);
        if (cmd->smpl[i])
            free(cmd->smpl[i]);
        i++;
    }
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
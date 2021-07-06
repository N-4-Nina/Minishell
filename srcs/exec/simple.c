#include "../../includes/nsh.h"

int     args_count(t_ast *node)
{
    int ac;

    ac = 0;
    while (node && (node->left->type == N_WORD || (node->type == N_CMD_SUFFIX && node->left->type != N_IO_FILE)))
    {
        ac++;
        node = node->right;
    }
    return (ac);
}
void    init_simple(t_smpl *s, int ac)
{
    
    s->argv = (char **)malloc(sizeof(char*) * (ac + 1));
    s->files = (int*)malloc(sizeof(int*));
    s->argc = 0;
    s->input = STDIN_FILENO;
    s->output = STDOUT_FILENO;
    s->filesnb = 0;
    s->isbuiltin = -1;
    s->path = NULL;
}

t_smpl *abort_simple(t_smpl *s)
{
    free(s->argv);
    free(s->files);
    free(s);
    return (NULL);
}

t_smpl *build_simple(t_sh *nsh, t_ast *node)
{
    t_smpl *s;
    int     ac;

    s = (t_smpl*)malloc(sizeof(t_smpl));
    ac = args_count(node);
    init_simple(s, ac);
    if (node->left->type == N_IO_FILE)
    {
        if (handle_io_first(s, node, nsh) == -1)
            return (abort_simple(s));
    }
    else
    {
        if (id_cmd_word(s, node, nsh) == -1)
            return (abort_simple(s));
    }
    s->argv[s->argc] = NULL;
    //s->argv[s->argc] = malloc(sizeof(char*));
    return (s);
}
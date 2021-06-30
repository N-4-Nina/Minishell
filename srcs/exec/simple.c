#include "../../includes/nsh.h"

void    init_simple(t_smpl *s)
{
    
    s->argv = (char **)malloc(sizeof(char*));
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

    s = (t_smpl*)malloc(sizeof(t_smpl));
    init_simple(s);
    if (node->left->type == N_IO_FILE)
    {
        if (handle_io_first(s, node, nsh) == -1)
            return (abort_simple(s));
    }
    else
        id_cmd_word(s, node, nsh);
    s->argv[s->argc + 1] = malloc(sizeof(char*));
    s->argv[s->argc + 1] = NULL;
    return (s);

}
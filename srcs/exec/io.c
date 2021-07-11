#include "../../includes/nsh.h"

int    handle_io_suf(t_smpl *s, t_ast *node, t_env *env)
{
    char    *hd;

    hd = find_by_name(env, "HEREDOC")->value;
    open_file(s, node->left->data, hd, get_flags(node->right->data));
    if (s->output == -1)
        return (-1);
    return (1);
}

int    handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh)
{
    t_ast *io_node;
    char    *hd;

    hd = find_by_name(nsh->env, "HEREDOC")->value;
    io_node = node->left;
    open_file(s, io_node->left->data, hd, get_flags(io_node->right->data));
    if (s->output == -1)
        return (-1);
    if (node->right)
    {
        node = node->right;
        id_cmd_word(s, node, nsh);
    }
    return (1);
}
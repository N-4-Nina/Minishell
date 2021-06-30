#include "../../includes/nsh.h"

int    handle_io_suf(t_smpl *s, t_ast *node)
{
    if (node->right->data[0] == '>' || !(ft_strncmp(node->right->data, "<", 2)))
        s->output = open_file(s, node->left->data, get_flags(node->right->data));
    // else
    //     handle <<
    if (s->output == -1)
        return (-1);
    return (1);
}

int    handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh)
{
    t_ast *io_node;

    io_node = node->left;
    s->output = open_file(s, io_node->left->data, get_flags(io_node->right->data));
    if (s->output == -1)
        return (-1);
    if (node->right)
    {
        node = node->right;
        id_cmd_word(s, node, nsh);
    }
    return (1);
}
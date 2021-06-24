#include "../../includes/nsh.h"

void    handle_io_suf(t_smpl *s, t_ast *node)
{
    // what the fuck is this condition doing ????
    if (node->right->data[0] == '>')
        s->output = open_file(s, node->left->data, get_flags(node->right->data));
    else
        s->input = open_file(s, node->left->data, get_flags(node->right->data));
}

void    handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh)
{
    t_ast *io_node;

    io_node = node->left;
    s->output = open_file(s, io_node->left->data, get_flags(io_node->right->data));
    if (node->right)
    {
        node = node->right;
        id_cmd_word(s, node, nsh);
    }    
}
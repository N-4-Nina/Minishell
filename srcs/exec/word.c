#include "../../includes/nsh.h"

void    id_cmd_suffix(t_smpl *s, t_ast *node, t_env *env)
{
    if (node->left->type == N_IO_FILE)
        handle_io_suf(s, node->left);
    else
        handle_word_suf(s, node->left, env);
}

void    id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh)
{
    char    *xpd;

    xpd = expand_word(node->left->data, nsh->env);
    if ((s->isbuiltin = is_builtin(xpd, nsh->bui)) != -1)
        (void)nsh;
    else if (!set_cmd_path(s, nsh->env, xpd))
        printf("Command not found: %s\n", node->left->data);
    s->argv[0] = ft_strdup(node->left->data);
    node = node->right;
    while (node)
    {
        
        id_cmd_suffix(s, node, nsh->env);
        node = node->right;
    }
}

void    handle_word_suf(t_smpl *s, t_ast *node, t_env *env)
{
    s->argc++;
    s->argv[s->argc] = expand_word(node->data, env);
}
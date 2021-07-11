#include "../../includes/nsh.h"

int    id_cmd_suffix(t_smpl *s, t_ast *node, t_env *env)
{
    if (node->left->type == N_IO_FILE)
        return (handle_io_suf(s, node->left, env));
    else
        return (handle_word_suf(s, node->left, env));
}

int    id_cmd_word(t_smpl *s, t_ast *node, t_sh *nsh)
{
    char    *xpd;

    xpd = expand_word(node->left->data, nsh->env);
    if ((s->isbuiltin = is_builtin(xpd, nsh->bui)) != -1)
        free(xpd);
    else if (!set_cmd_path(s, nsh->env, xpd))
    {
        printf("Nsh: Command not found: %s\n", node->left->data);
        return (-1);
    }
    s->argv[0] = ft_strdup(node->left->data);
    s->argc++;
    node = node->right;
    while (node)
    {
        if (id_cmd_suffix(s, node, nsh->env) == -1)
            return (-1);
        node = node->right;
    }
    return (1);
}

int    handle_word_suf(t_smpl *s, t_ast *node, t_env *env)
{
    s->argv[s->argc] = expand_word(node->data, env);
    s->argc++;
    return (1);
}
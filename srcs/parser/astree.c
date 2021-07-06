#include "../../includes/nsh.h"

t_ntype convert_type(t_ttype type)
{
    if (type >= DGREAT && type <= LESS)
        return (N_RED);
    if (type == PIPE)
        return (N_PIPE_SEQ);
    if (type == SEMI)
        return (N_CMD);
    if (type == WORD)
        return (N_WORD);
    else
        return (N_WORD);
}

t_ast   *new_node(t_ntype type, char *data)
{
    t_ast   *new;

    new = malloc(sizeof(t_ast));
    if (!new)
        return (NULL);
    new->data = data;
    new->type = type;
    if (data)
        new->len = ft_strlen(data);
    new->left = NULL;
    new->right = NULL;

    return (new);
}

t_ast   *node_from_tok(t_tok tok)
{
    t_ast   *new;

    new = malloc(sizeof(t_ast));
    if (!new)
        return (NULL);
    //if (tok.type == WORD || (tok.type >= DGREAT && tok.type < SEMI))
    //    new->data = ft_strdup(tok.data);
    //else
        new->data = tok.data;
    new->len = tok.len;
    new->type = convert_type(tok.type);
    new->left = NULL;
    new->right = NULL;

    return (new);
}

void    free_node(t_ast *node, int free_data)
{
    if (node->data && free_data)
        free(node->data);
    if (node)
        free(node);
}

void    graft_node_left(t_ast **node, t_ast *new)
{
    t_ast   *current;

    if (!node || !new)
        return;
    if (!*node)
    {
        *node = new;
        return ;
    }
    current = *node;
    while (current->left)
    {
        *node = (*node)->left;
        printf("jumping to left node\n");
    }
    (*node)->left = new;
}

void    graft_node_right(t_ast **node, t_ast *new)
{
    t_ast *current;

    if (!node || !new)
       return;
    if (!*node)
    {
        *node = new;
        printf("node is NULL (%s) \n", new->data);
        return ;
    }
   current = *node;
    while (current->right)
    {
        *node = (*node)->right;
        printf("jumping to right node: %s \n", (*node)->data);
    }
    (*node)->right = new;
}

void    ast_reset(t_ast **node)
{
    if (!node || !*node)
        return;
    if ((*node)->left)
        ast_reset(&(*node)->left);
    if ((*node)->right)
        ast_reset(&(*node)->right);

    free_node((*node), 1);
}

int     tree_init(t_sh *nsh)
{
    nsh->ast = new_node(N_PROGRAM, ft_strdup("Program"));
    if (!nsh->ast)
        return (0);
    return (1);
}
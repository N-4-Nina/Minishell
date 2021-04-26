#include "../../includes/nsh.h"

t_ntype convert_type(t_ttype type)
{
    if (type >= 0 && type <= 2)
        return (N_RED);
    if (type == 3)
        return (N_PIPE_SEQ);
    if (type == 4)
        return (N_CMD);
    if (type == 5)
        return (N_WORD);
    else
        return (6);
}

t_ast   *new_node(t_ntype type, char *data)
{
    t_ast   *new;

    if (!(new = malloc(sizeof(t_ast))))
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

    if (!(new = malloc(sizeof(t_ast))))
        return (NULL);
    
    if (tok.type == 5 || (tok.type >= 0 && tok.type < 4))
        new->data = ft_strdup(tok.data);
    else
        new->data = tok.data;
    new->len = tok.len;
    new->type = convert_type(tok.type);
    new->left = NULL;
    new->right = NULL;

    return (new);
}

void    free_node(t_ast *node)
{
    if (node->data)
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
    if (node || !*node)
        return;
    if ((*node)->left)
        ast_reset(&(*node)->left);
    if ((*node)->right)
        ast_reset(&(*node)->right);

    free_node((*node));  
}

int     tree_init(t_sh *nsh)
{ 
    if (!(nsh->ast = new_node(N_PROGRAM, ft_strdup("Program"))))
        return (0);
    return (1);
}
#include "../includes/nsh.h"

char hex_digit(int i)
{
    if (i >= 0 && i < 10)
        return ('0' + i);
    else
        return ('a' + i - 10);
}

void toHex(void *ptr, int fd)
{
    int i;
    char buf[1];
    uintptr_t p;
    
    p = (uintptr_t)ptr;
    i = (sizeof(p) << 3)- 4;
    write(fd, "0", 1);
    write(fd, "x", 1);
    while(i >= 0)
    {
        buf[0] = hex_digit((p >> i) & 0xf);
        write(fd, buf, 1);
        i-=4;
    }
}

void write_node_name(t_ast **node, int fd)
{
    if ((*node)->data)
        write(fd, (*node)->data, ft_strlen((*node)->data));
    else
        write(fd, &(*node)->type, sizeof(int));
    write(fd, "\\n", 2);
    toHex(*node, fd);
    write(fd, "\"", 1);
    write(fd, " -> ", 4);
}

void    write_empty_left(int fd, t_ast **node)
{
    write(fd, "L_BRANCH", 8);
    write(fd, "\\n", 2);
    toHex(*node, fd);
    write(fd, "\"", 1);
    write(fd, ";\n", 2);

    write(fd, "\"", 1);
    write(fd, "L_BRANCH", 8);
    write(fd, "\\n", 2);
    toHex(*node, fd);
    write(fd, "\"", 1);
    write(fd, " [shape=none fontsize=8]\n", 25);
}

void    write_empty_right(int fd, t_ast **node)
{
    write(fd, "R_BRANCH", 8);
    write(fd, "\\n", 2);
    toHex(*node, fd);
    write(fd, "\"", 1);
    write(fd, ";\n", 2);

    write(fd, "\"", 1);
    write(fd, "R_BRANCH", 8);
    write(fd, "\\n", 2);
    toHex(*node, fd);
    write(fd, "\"", 1);
    write(fd, " [shape=none fontsize=8]\n", 25);
}

void write_redir(int fd, char *data)
{
    if (ft_strlen(data) == 2)
        write(fd, "DGREAT", 6);
    else if (data[0] == '>')
        write(fd, "GREAT", 5);
    else
        write(fd, "LESS", 4);
    
}

void write_left(t_ast **node, int fd)
{
    write(fd, "\"", 1);
    if ((*node)->left)
    {
        if ((*node)->left->data)
        {
            if ((*node)->left->data[0] == '>' || (*node)->left->data[0] == '<')
                write_redir(fd, (*node)->left->data);
            else
                write(fd, (*node)->left->data, ft_strlen((*node)->left->data));
        }
        else
            write(fd, &(*node)->right->type, sizeof(int));
        write(fd, "\\n", 2);
        toHex((*node)->left, fd);
    }
    else
    { 
        write_empty_left(fd, node);
        return;
    }
    write(fd, "\"", 1);
    write(fd, ";\n", 2);

}
void write_right(t_ast **node, int fd)
{
    write(fd, "\"", 1);
    if ((*node)->right)
    {
        if ((*node)->right->data)
        {
            if ((*node)->right->data[0] == '>' || (*node)->right->data[0] == '<')
                write_redir(fd, (*node)->right->data);
            else
                write(fd, (*node)->right->data, ft_strlen((*node)->right->data));
        }            
        else
            write(fd, &(*node)->right->type, sizeof(int));
        write(fd, "\\n", 2);
        toHex((*node)->right, fd);
    }
    else
    {
        write_empty_right(fd, node);
        return;
    }
    write(fd, "\"", 1); 
    write(fd, ";\n", 2);
}

void write_rules(t_ast **node, int fd)
{
    write(fd, "\"", 1);
    if ((*node)->data[0] == '>' || (*node)->data[0] == '<')
    {
        write_redir(fd, (*node)->data);
        write(fd, "\\n", 2);
        toHex(*node, fd);
        write(fd, "\"", 1);
        write(fd, " -> ", 4);      
    }
    else
        write_node_name(node, fd);
   
    write_left(node, fd);
    write(fd, "\"", 1);
    if ((*node)->data[0] == '>' || (*node)->data[0] == '<')
    {
        write_redir(fd, (*node)->data);
        write(fd, "\\n", 2);
        toHex(*node, fd);
        write(fd, "\"", 1);
        write(fd, " -> ", 4);

    }
    else
        write_node_name(node, fd);
    write_right(node, fd);
}

void    visit_node(t_ast **node, int fd)
{
    write_rules(node, fd);

    if ((*node)->left)
        visit_node(&(*node)->left, fd);
    if ((*node)->right)
        visit_node(&(*node)->right, fd);
}

void    write_dot(t_ast **node)
{
    int fd;

    remove("graph.dot");
    fd = open("graph.dot", O_CREAT|O_WRONLY, S_IRWXU);
    write(fd, "digraph graphname {\n", 20);
    visit_node(node, fd);
    write(fd, "\n}", 2);
    close(fd);
}
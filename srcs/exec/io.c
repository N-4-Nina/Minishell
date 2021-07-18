#include "../../includes/nsh.h"

int	handle_io_suf(t_smpl *s, t_ast *node, t_env *env, int *status)
{
	char	*hd;
	char	*xpd;

	hd = find_by_name(env, "HEREDOC")->value;
	if (ft_strncmp(node->right->data, "<<", 3))
		xpd = expand_word(node->left->data, env, status);
	else
		xpd = ft_strdup(node->left->data);
	open_file(s, xpd, hd, get_flags(node->right->data));
	free(xpd);
	if (s->output == -1)
		return (-1);
	return (1);
}

int	handle_io_first(t_smpl *s, t_ast *node, t_sh *nsh)
{
	t_ast	*io_node;
	char	*hd;
	char	*xpd;

	hd = find_by_name(nsh->env, "HEREDOC")->value;
	io_node = node->left;
	if (ft_strncmp(io_node->right->data, "<<", 3))
		xpd = expand_word(io_node->left->data, nsh->env, nsh->last_status);
	else
		xpd = ft_strdup(io_node->left->data);
	open_file(s, xpd, hd, get_flags(io_node->right->data));
	free(xpd);
	if (s->output == -1)
		return (-1);
	node = node->right;
	while (node)
	{	
		if (node->left->type == N_WORD)
			id_cmd_word(s, node, nsh);
		else if (node->left->type == N_IO_FILE)
			handle_io_suf(s, node->left, nsh->env, nsh->last_status);
		node = node->right;
	}
	return (1);
}

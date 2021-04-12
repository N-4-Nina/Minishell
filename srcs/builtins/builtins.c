/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 09:26:49 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:35:12 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	nsh_echo(t_env *env, char **args)
{
	int	i;

	i = 1;
	(void)env;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	nsh_cd(t_env *env, char **args)
{
	t_env	*var;

	if(!chdir(args[1]))
	{
		var = find_by_name(env, "PWD");
		getcwd(var->value, 4096);
	}

	return (0);
}

int	nsh_pwd(t_env *env, char **args)
{
	t_env	*var;

	args[0][0] = 'p'; 
	var = find_by_name(env, "PWD");
	write(1, var->value, ft_strlen(var->value));
	write(1, "\n", 1);
	return (0);
}

int	nsh_export(t_env *env, char **args)
{
	int	i;
	char	**split;
	t_env	*node;

	i = 1;
	while(args[i])
	{
		split = ft_split(args[i], '=');
		if ((node = find_by_name(env, split[0])))
		{
			free(node->value);
			free(node->name);
			node->name = split[0];
			node->value = split[1];
		}
		else
			add_var(env, split[0], split[1]);
		i++;
	}
	return (0);
}

void	remove_var(t_env *env, t_env *node)
{
	t_env	*lst;

	lst = env;
	if (lst == node)
	{
		env = lst->next;
		free(lst->name);
		free(lst->value);
		free(lst);
		return;
	}
	while (lst->next != node)
		lst = lst->next;
	lst->next = node->next;
	free(node->name);
	free(node->value);
	free(node);
}

int	nsh_unset(t_env *env, char **args)
{
	int	i;
	t_env	*node;

	i = 1;
	while (args[i])
	{
		node = NULL;
		if ((node = find_by_name(env, args[i])))
			remove_var(env, node);
		i++;
	}
	return (0);
}

int	nsh_env(t_env *env, char **args)
{
	t_env	*lst;

	args[0][0] = 'e';
	lst = env;
	while (lst)
	{
		write(1, lst->name, ft_strlen(lst->name));
		write(1, "=", 1);
		write(1, lst->value, ft_strlen(lst->value));
		write(1, "\n", 1);
		lst = lst->next;
	}
	return (0);
}

int	nsh_exit(t_env *env, char **args)
{
	//should free everything... maybe reconfigure builtins to accept nsh instead env
	(void)env;
	args[0][0] = args[0][0];
	exit(EXIT_SUCCESS);
	return (0);
}

// void	bui_init(t_sh *nsh)
// {
// 	char	*builtin_str[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
// 	int	(*builtin_func[]) (t_env *, char **) = {&nsh_echo, &nsh_cd, &nsh_pwd, &nsh_export,
//        					&nsh_unset, &nsh_env, &nsh_exit};
	
// 	//nsh->bui->builtin_str = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
// 	//nsh->bui->builtin_func = {&nsh_echo, &nsh_cd, &nsh_pwd, &nsh_export,
//     //   					&nsh_unset, &nsh_env, &nsh_exit};
// }
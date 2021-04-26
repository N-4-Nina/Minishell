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

int	is_builtin(char *s, t_bui b)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(s, b.str[i], ft_strlen(s)))
			return (1);
		i++;
	}
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
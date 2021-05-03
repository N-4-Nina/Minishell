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

int	is_builtin(char *s, t_bui *b)
{
	int	i;
	size_t	size;

	i = 0;
	if (!s)
		return(-1);
	size = ft_strlen(s);
	while (i < 7)
	{
		if (size != ft_strlen(b->str[i]))
		{
			i++;
			continue;
		}
		if (!ft_strncmp(s, b->str[i], ft_strlen(s)))
			return (i);
		i++;
	}
	return (-1); 
}

void	bui_init(t_sh *nsh)
{
	int  i;
 	char	builtin_str[7][7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int	(*builtin_func[7]) (t_sh *, char **) = {&nsh_echo, &nsh_cd, &nsh_pwd, &nsh_export,
       					&nsh_unset, &nsh_env, &nsh_exit};
	
	i = 0;
	nsh->bui->str = (char **)malloc(sizeof(builtin_str));
	while (i < 7)
	{
		nsh->bui->str[i] = ft_strdup(&builtin_str[i][0]);
		nsh->bui->func[i] = builtin_func[i];
		i++;
	}
}
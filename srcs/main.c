/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/17 22:33:34 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

/*
   char	**nsh_parse(char *line)
   {
   char	**tokens;

   tokens = ft_split(line, ' ');
   return (tokens);
   }
   */

int	nsh_cd(char **args)
{
	write(1, args[0], ft_strlen(args[0]));
	return (0);
}

int	nsh_exit(char **args)
{
	write(1, args[0], ft_strlen(args[0]));
	return (0);
}

char	*g_builtin_str[] = {"cd", "exit"};

int	(*g_builtin_func[]) (char **) = {&nsh_cd, &nsh_exit};


int	nsh_execute(char **args)
{
	int i;

	if (args[0] == NULL)
		return (1);
	i = 0;	  
	while (i < 2)
	{
		if (ft_strncmp(args[0], g_builtin_str[i], 5) == 0)
			return (*g_builtin_func[i])(args);
		i++;
	}
	
	return (0);
	//return lsh_launch(args);
}

int	nsh_loop(void)
{
	int	status;
	char	*line;
	char	**tokens;

	status = 1;

	while (status)
	{
		write(1, "> ", 2);
		get_next_line(0, &line);
		tokens = ft_split(line, ' ');
		nsh_execute(tokens);
		//status = 0;
	}
	return(status);
}

int	main(void)
{
	ft_strlen("blabla");
	nsh_loop();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:28:28 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	isRedirect(char *token)
{
	return(ft_strncmp("|", token, ft_strlen(token)) ||
		ft_strncmp(">", token, ft_strlen(token) ||
			ft_strncmp("<", token, ft_strlen(token))));
}

char	*g_builtin_str[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

int	(*g_builtin_func[]) (char **) = {&nsh_echo, &nsh_cd, &nsh_pwd, &nsh_export,
       					&nsh_unset, &nsh_env, &nsh_exit};

t_env	**g_env;

void display_tokens(char **tokens)
{
	int i = 0;

	while (tokens[i])
			{
				write(1, "-------------------\n", 21);
				//write(1, "\n", 1);
				write(1, tokens[i], ft_strlen(tokens[i]));
				write(1, "\n", 1);
				i++;
			}
}

int	nsh_loop()
{
	int	status;
	int	toknb;
	char	*line;
	char	**tokens;

	status = 1;
	toknb = 0;

	while (status)
	{
		display_prompt();
		get_next_line(0, &line);
		if (line[0] == 4)
			status = 0;
		if (line[0] == 3 || line[0] == 4)
			continue;
		//tokens = ft_split(line, ' ');
		tokens = parse(line, &toknb);
		
		interpret(tokens, toknb);
		free_tokens(tokens);
		//nsh_execute(tokens);
		//status = 0;
	}
	return(status);
}

int	main(void)
{
	env_init();
	nsh_loop();
	return (0);
}

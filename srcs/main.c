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


int	nsh_launch(char **args)
{
	int	status;
	pid_t	pid;
	pid_t	wpid;
	char	*path;
	char **env = env_to_array();

	pid = fork();
	if (pid == -1)
		return(-1);
	if (pid == 0)
	{
		if(execve(args[0], args, env) == -1)
		//	write(1, "couldn't exec, looking in PATH...\n", 25);
		path = ft_strjoin(find_by_name("PATH")->value, args[0]);
		if(execve(path, args, env) == -1)
		//	write(1, "couldn't find in path either\n", 20);
		free(path);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}


int	nsh_execute(char **args)
{
	int i;

	if (args[0] == NULL)
		return (1);
	i = 0; 
	while (i < 7)
	{
		if (ft_strncmp(args[0], g_builtin_str[i], 5) == 0)
			return (*g_builtin_func[i])(args);
		i++;
	}
	
	//return (0);
	return nsh_launch(args);
}
/*
int	nsh_interpret(char **tokens)
{
	int	i;
	int	j;
	char	**args;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (!isRedirect(tokens[i]))
		{
			ft_memcpy(args[j], tokens[i], ft_strlen(tokens[i]));
			j++;
			i++;
		}
	}
}
*/
void	display_prompt()
{
	char **split;
	t_env	*var;
	int	i;

	i = 0;
	var = find_by_name("PWD");
	split = ft_split(var->value, '/');
	while (split[i])
		i++;
	write(1, split[i-1], ft_strlen(split[i-1]));
	write(1, " -> ", 4);
}

int	nsh_loop()
{
	int	status;
	char	*line;
	char	**tokens;

	status = 1;

	while (status)
	{
		display_prompt();
		get_next_line(0, &line);
		if (line[0] == 4)
			status = 0;
		if (line[0] == 3 || line[0] == 4)
			continue;
		tokens = ft_split(line, ' ');
		nsh_execute(tokens);
		//nsh_interpret(tokens); not ready
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

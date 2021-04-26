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

int exec_seq(t_inter *in, t_seq *s)
{
    int i;
    int *fd[2];  //should probably be in seq

    i = 0;
	while (i < s -> rednb)
	{
    	fd[i] = (int*)malloc(sizeof(int) * 2);
        pipe(fd[i++]);
	}
	i = 0;
	while (i < s->cmdnb)
	{

	}
}

/* IMPORTED FROM MAIN */

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
		if (execve(args[0], args, env) == -1)
		//	write(1, "couldn't exec, looking in PATH...\n", 25);
		path = ft_strjoin(find_by_name("PATH")->value, args[0]);
		if (execve(path, args, env) == -1)
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
	return nsh_launch(args);
}
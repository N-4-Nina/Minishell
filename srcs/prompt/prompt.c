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

char	*get_dir_name(t_env *env)
{
	char	**split;
	char	*ret;
	t_env	*var;
	int		i;

	i = 0;
	var = find_by_name(env, "PWD");
	if (!var)
		return (NULL);
	if (!(ft_strncmp(var->value, "/", 2)))
		ret = ft_strdup("/");
	else
	{
		split = ft_split(var->value, '/');
		while (split[i])
			i++;
		ret = ft_strdup(split[i - 1]);
		free_array(split, i);
	}
	return (ret);
}

void	build_prompt(t_env *env, t_inp *inp)
{	
	int		i;
	int		j;
	int		len;
	char	*s;

	i = 0;
	j = 0;
	s = get_dir_name(env);
	len = ft_strlen(s);
	inp->prompt = malloc(len + 10 + BOLD_SIZE * 2 + (COLOR_SIZE + 1 * 3));
	ft_bzero(inp->prompt, len + 10 + BOLD_SIZE * 2 + (COLOR_SIZE + 1 * 3));
	j += ft_strlcat(&inp->prompt[j], SET_BOLD, BOLD_SIZE + 1);
	j += ft_strlcat(&inp->prompt[j], SET_BLUE, COLOR_SIZE + 1);
	j += ft_strlcat(&inp->prompt[j], s, len + 1);
	j += ft_strlcat(&inp->prompt[j], SET_YELLOW, COLOR_SIZE + 1);
	j += ft_strlcat(&inp->prompt[j], " -> ", 5);
	j += ft_strlcat(&inp->prompt[j], SET_WHITE, COLOR_SIZE);
	j += ft_strlcat(&inp->prompt[j], SET_LIGHT, BOLD_SIZE + 1);
	i = 0;
	free(s);
}

// void	display_prompt(t_env *env)
// {
// 	char **split;
// 	t_env	*var;
// 	int	i;

// 	i = 0;
// 	var = find_by_name(env, "PWD");
// 	if (!var)
// 		return;
// 	split = ft_split(var->value, '/');
// 	while (split[i])
// 		i++;
// 	inp->promptsize =  ft_strlen(split[i-1]) + 4;
// 	inp-> curX = inp->promptsize;
// 	write(1, SET_BLUE, COLOR_SIZE);
// 	write(1, split[i-1], );
// 	write(1, SET_YELLOW, COLOR_SIZE);
// 	write(1, " -> ", 4);
// 	write(1, SET_WHITE, COLOR_SIZE-1);
// 	i = 0;
// 	while(split[i])
// 		free(split[i++]);
// 	free(split); 
// }

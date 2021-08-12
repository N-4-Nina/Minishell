/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/08/11 17:53:43 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/environment.h"
#include "../includes/utils.h"
#include "../includes/defines.h"

char	*get_dir_name(t_env *env)
{
	char	**split;
	char	*ret;
	t_env	*var;
	int		i;

	i = 0;
	var = find_by_name(env, "PWD");
	if (!var)
	{
		ret = malloc(2);
		ret[0] = '?';
		ret[1] = 0;
		return (ret);
	}
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

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

void	display_prompt(t_env *env, t_inp *inp)
{
	char **split;
	t_env	*var;
	int	i;

	i = 0;
	var = find_by_name(env, "PWD");
	if (!var)
		return;
	split = ft_split(var->value, '/');
	while (split[i])
		i++;
	inp->promptsize =  ft_strlen(split[i-1]) + 4;
	inp-> curX = inp->promptsize;
	write(1, SET_BLUE, COLOR_SIZE);
	write(1, split[i-1], ft_strlen(split[i-1]));
	write(1, SET_YELLOW, COLOR_SIZE);
	write(1, " -> ", 4);
	write(1, SET_WHITE, COLOR_SIZE-1);
	i = 0;
	while(split[i])
		free(split[i++]);
	free(split); 
}
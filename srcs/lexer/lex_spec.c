/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_spec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:15:01 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 17:21:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	handle_blank(t_lex *l)
{
	while (l->inp[l->i] && isBlank(l->inp[l->i]))
		l->i++;
}

int	set_spec_type(t_lex *l)
{
	static char	*types[6] = {">>", ">", "<<", "<", "|", ";"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (!(ft_strncmp(l->t[l->j].data, types[i], 3)))
			return (l->t[l->j].type = i);
		i++;
	}
	return (-1);
}

void	handle_spec(t_lex *l)
{
	set_spec_len(l);
	copy_data(l, 1);
	set_spec_type(l);
	progress(l, 0);
}

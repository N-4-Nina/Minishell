/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:56:36 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/11 11:23:30 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_white_spaces(const char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int		minus_signs;
	int		i;
	long	nb;

	minus_signs = 0;
	nb = 0;
	i = count_white_spaces(str);
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			minus_signs++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (minus_signs % 2 != 0)
		nb = -nb;
	return (nb);
}

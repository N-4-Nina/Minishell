/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:41:19 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/07 11:00:24 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t				i;
	unsigned	char	value;

	i = 0;
	value = (unsigned char)c;
	while (i < len)
	{
		*(unsigned char *)b = value;
		b++;
		i++;
	}
	b -= len;
	return (b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:55:56 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/08 15:01:23 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	do_copy(unsigned char *dest,
		unsigned char *sour, size_t i, size_t len)
{
	if (dest > sour)
	{
		while (i < len)
		{
			dest[len - 1] = sour[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			dest[i] = sour[i];
			i++;
		}
	}
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned	char	*destcast;
	unsigned	char	*sourcast;

	destcast = (unsigned char *)dst;
	sourcast = (unsigned char *)src;
	i = 0;
	if (dst == NULL && src == NULL && len)
		return (dst);
	do_copy(destcast, sourcast, i, len);
	return (dst);
}

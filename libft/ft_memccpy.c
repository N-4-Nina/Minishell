/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:40:18 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/04 14:53:45 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		i++;
		if (*(unsigned char*)src == (unsigned char)c)
		{
			dst++;
			return (dst);
		}
		else
		{
			dst++;
			src++;
		}
	}
	return (NULL);
}

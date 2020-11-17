/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:29:42 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/07 11:08:28 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char*)s1 != *(unsigned char*)s2)
			return (*(unsigned char*)s1 - *(unsigned char*)s2);
		i++;
		s1++;
		s2++;
	}
	return (0);
}

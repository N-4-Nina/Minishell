/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:47:47 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/12 15:53:49 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*link;
	t_list	*next;

	link = *lst;
	if (lst == 0 || del == 0)
		return ;
	while (link)
	{
		next = link->next;
		del(link->content);
		free(link);
		link = next;
	}
	*lst = NULL;
}

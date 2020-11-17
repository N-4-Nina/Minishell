/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:57:17 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/12 16:54:40 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		i;
	t_list	*new;
	t_list	*begin;
	t_list	*tmplink;

	i = ft_lstsize(lst);
	if (!lst)
		return (NULL);
	tmplink = lst;
	if (!(begin = ft_lstnew(f(tmplink->content))))
		return (NULL);
	tmplink = tmplink->next;
	while (tmplink)
	{
		if (!(new = ft_lstnew(f(tmplink->content))))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, new);
		tmplink = tmplink->next;
	}
	return (begin);
}

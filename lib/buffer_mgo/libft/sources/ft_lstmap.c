/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:06:16 by mgo               #+#    #+#             */
/*   Updated: 2021/05/17 16:03:24 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*first;

	new_lst = (t_list *)malloc(sizeof(t_list *));
	if (!new_lst)
		return (NULL);
	first = new_lst;
	while (lst)
	{
		new_lst->content = f(lst->content);
		lst = lst->next;
		if (!lst)
			break ;
		new_lst->next = (t_list *)malloc(sizeof(t_list *));
		if (!new_lst->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new_lst = new_lst->next;
	}
	new_lst->next = NULL;
	return (first);
}

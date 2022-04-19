/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:03:59 by bson              #+#    #+#             */
/*   Updated: 2021/05/11 18:19:43 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list_current;
	t_list	*list_delete;

	if (lst == NULL || del == NULL)
		return ;
	list_current = *lst;
	while (list_current != NULL)
	{
		list_delete = list_current;
		list_current = list_current->next;
		ft_lstdelone(list_delete, del);
	}
	*lst = NULL;
}

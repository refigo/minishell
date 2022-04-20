/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:29:05 by bson              #+#    #+#             */
/*   Updated: 2021/05/11 18:34:39 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*list_current;

	if (lst == NULL || f == NULL)
		return ;
	list_current = lst;
	while (list_current != NULL)
	{
		f(list_current->content);
		list_current = list_current->next;
	}
}

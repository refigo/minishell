/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:20 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:54:05 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_tok_list	*new_tok_list(void)
{
	t_tok_list	*list;

	list = malloc(sizeof(t_tok_list));
	ft_assert(list != NULL, "ERROR : leak resource in new_tok_list()");
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_tok	*new_token(char *tok)
{
	t_tok	*ret;

	ret = malloc(sizeof(t_tok));
	ft_assert(ret != NULL, "ERROR : leak resource in new_token()");
	ret->token = tok;
	ret->type = TOK_TYPE_UNDEFINE;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

void	remove_token_list(t_tok_list **list)
{
	t_tok	*iter;
	t_tok	*iter_next;
	int		cnt;

	cnt = 0;
	iter = (*list)->head;
	while (cnt < (*list)->size)
	{
		iter_next = iter->next;
		free(iter->token);
		free(iter);
		iter = iter_next;
		++cnt;
	}
	ft_free((void **)list);
}

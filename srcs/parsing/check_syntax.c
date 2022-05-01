/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:43 by bson              #+#    #+#             */
/*   Updated: 2022/04/30 15:02:54 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdio.h>

int	syntax_check_pipe(t_tok *node, t_tok_list *list)
{
	if (node->type == TOK_TYPE_PIPE)
	{
		if (node->next == list->head)
			return (-1);
	}
	return (0);
}

int	syntax_check_file(t_tok *node, t_tok_list *list)
{
	if (node->type == TOK_TYPE_REDIR && node == list->tail)
		return (-1);
	if (node->type == TOK_TYPE_REDIR && node->next->type == TOK_TYPE_PIPE)
		return (-1);
	return (0);
}

int	check_syntax(t_tok_list *list)
{
	int		cnt;
	t_tok	*iter;

	cnt = -1;
	iter = list->head;
	if (list->tail->type == TOK_TYPE_PIPE)
		return (-1);
	while (++cnt < list->size)
	{
		if (syntax_check_pipe(iter, list))
			return (-1);
		if (syntax_check_file(iter, list))
			return (-1);
		iter = iter->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:03 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 20:16:32 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdio.h>

static int	check_special(t_tok *iter, bool *flag)
{
	if (iter->token[0] == '|')
	{
		iter->type = TOK_TYPE_PIPE;
		ft_bzero(flag, sizeof(bool) * 2);
		return (true);
	}
	else if (ft_strchr("<>", iter->token[0]))
	{
		iter->type = TOK_TYPE_REDIR;
		flag[FLAG_REDIR] = true;
		return (true);
	}
	return (false);
}

static void	check_normal(t_tok *iter, bool *flag)
{
	if (flag[FLAG_CMD] || flag[FLAG_REDIR])
	{
		if (flag[FLAG_REDIR])
		{
			iter->type = TOK_TYPE_FILE;
			flag[FLAG_REDIR] = false;
		}
		else
		{
			iter->type = TOK_TYPE_ARG;
		}
	}
	else
	{
		iter->type = TOK_TYPE_CMD;
		flag[FLAG_CMD] = true;
	}
}

int	lexer(t_tok_list *tok_list)
{
	bool	flag[2];
	bool	type;
	int		cnt;
	t_tok	*it;

	ft_bzero(flag, sizeof(bool) * 2);
	cnt = 0;
	it = tok_list->head;
	while (cnt < tok_list->size)
	{
		type = check_special(it, flag);
		if (type == false)
			check_normal(it, flag);
		remove_quotes(it);
		it = it->next;
		++cnt;
	}
	if (check_syntax(tok_list))
	{
		ft_putendl_fd("Syntax Error", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

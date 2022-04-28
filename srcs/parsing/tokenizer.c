/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:57 by bson              #+#    #+#             */
/*   Updated: 2022/04/28 16:33:07 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "env_manager.h"

char	*jump_quotes(char *cur, int c, int escape)
{
	if ((c != '\'' && c != '\"') || escape == true)
		return (cur);
	while (*cur != '\0')
	{
		if (c == '\'')
		{
			cur = ft_strchr(cur + 1, '\'');
			break ;
		}
		else
		{
			cur = ft_strchr(cur + 1, c);
			if (cur == NULL || *(cur - 1) != '\\')
				break ;
		}
	}
	return (cur);
}

t_tok_list	*tokenizer(char *input)
{
	t_tok_list	*ret;
	char		*begin;
	char		*end;

	ret = new_tok_list();
	begin = input;
	while (*begin)
	{
		while (ft_isspace(*begin))
			++begin;
		end = begin;
		while (*end && !ft_strchr("<>|", *begin) && !ft_strchr("<>| ", *end))
			end = jump_quotes(end, *end, \
					(end != begin && *(end - 1) == '\\')) + 1;
		if (ft_strchr("<>|", *begin) || (end - begin == 1 && *begin == '\\'))
			++end;
		if (*begin && *begin == *(begin + 1) && ft_strchr("<>", *begin))
			++end;
		if (*begin)
		{
			insert_tok_end(ret, new_token(ft_substr(begin, 0, end - begin)));
			begin = end;
		}
	}
	return (ret);
}

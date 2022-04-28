/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:12 by bson              #+#    #+#             */
/*   Updated: 2022/04/28 13:43:31 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static int	calc_quote_and_escape(char *input)
{
	char	*it;
	int		cnt;

	cnt = 0;
	it = input;
	while (*it != '\0')
	{
		if (*it == '\\')
			++cnt;
		if (ft_strchr("\'\"", *it) && (input == it || *(it - 1) != '\\'))
			cnt += 2;
		if (ft_strchr("\'\"", *it) != NULL)
			it = jump_quotes(it, *it, (it != input && *(it - 1) == '\\')) + 1;
		if (*it != '\0')
			++it;
	}
	return (cnt);
}


static void	remove_quote_and_escape(char *dest, char *src)
{
	bool	qoute_flag;
	int		s_idx;
	int		d_idx;

	qoute_flag = false;
	s_idx = 0;
	d_idx = 0;
	while (src[s_idx] != '\0')
	{
		if (src[s_idx] == '\\' && qoute_flag == false)
			++s_idx;
		if (ft_strchr("\'\"", src[s_idx]) \
			&& (s_idx == 0 || src[s_idx - 1] != '\\'))
		{
			qoute_flag = !qoute_flag;
			++s_idx;
		}
		dest[d_idx++] = src[s_idx++];
	}
}

static void	overwrite_array(char *start)
{
	char	*remover[2];

	if (start == NULL || *(start) == '\0')
		return ;
	remover[0] = start;
	remover[1] = start + 1;
	while(*remover[1] != '\0')
	{
		*remover[0] = *remover[1];
		++remover[0];
		++remover[1];
	}
	*remover[0] = *remover[1];
}

static void	remove_escape(char *array)
{

}

static void	remove_quote(char *array)
{
	char	*temp;
	int		quote_flag;

	quote_flag = 0;
	temp = array;
	while (*temp != '\0')
	{
		if (quote_flag == 0 && ft_strchr("\\\'\"", *temp))
		{
			if (*temp != '\\')
				quote_flag = *temp;
			overwrite_array(temp);
			continue;
		}
		if (quote_flag != 0 && (temp == node->token || *(temp - 1) != '\\'))
		{

		}
	}
}

void	remove_quotes(t_tok *node)
{
	char	*temp;
	char	*ret;
	int		quote_flag;

	quote_flag = 0;
	temp = node->token;


	free(node->token);
	node->token = temp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:12 by bson              #+#    #+#             */
/*   Updated: 2022/04/28 18:39:02 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

static void	overwrite_array(char *start)
{
	char	*remover[2];

	if (start == NULL || *(start) == '\0')
		return ;
	remover[0] = start;
	remover[1] = start + 1;
	while (*remover[1] != '\0')
	{
		*remover[0] = *remover[1];
		++remover[0];
		++remover[1];
	}
	*remover[0] = *remover[1];
}

static char	*state_single_quote(char *s_quote)
{
	if (s_quote == NULL)
		ft_assert(false, "Not NULL pointer in state_single_quote()");
	overwrite_array(s_quote);
	s_quote = ft_strchr(s_quote, '\'');
	overwrite_array(s_quote);
	return (s_quote);
}

static char	*state_double_quote(char *d_quote)
{
	if (d_quote == NULL)
		ft_assert(false, "Not NULL pointer in state_double_quote()");
	overwrite_array(d_quote);
	while (1)
	{
		if (*d_quote == '\\' && *(d_quote + 1) == '\"')
		{
			overwrite_array(d_quote);
			++d_quote;
		}
		else if (*d_quote == '\"')
		{
			overwrite_array(d_quote);
			break ;
		}
		else
			++d_quote;
	}
	return (d_quote);
}

void	remove_quotes(t_tok *node)
{
	char	*not_quote;
	char	*ret;

	not_quote = node->token;
	while (*not_quote != '\0')
	{
		if (*not_quote == '\\')
		{
			overwrite_array(not_quote);
			++not_quote;
		}
		else if (*not_quote == '\"' && \
		(not_quote == node->token || *(not_quote - 1) != '\\'))
			not_quote = state_double_quote(not_quote);
		else if (*not_quote == '\'' && \
		(not_quote == node->token || *(not_quote - 1) != '\\'))
			not_quote = state_single_quote(not_quote);
		else
			++not_quote;
	}
	ret = ft_strdup(node->token);
	ft_assert(ret != NULL, "leak resource in remove_quotes()");
	free(node->token);
	node->token = ret;
}

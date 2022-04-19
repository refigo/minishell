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
		if (ft_strchr("\'\"", *it) && (input == it || *(it - 1) != '\\'))
			it = jump_quotes(it, *it) + 1;
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

void	remove_quotes(t_tok *node)
{
	char	*temp;

	temp = ft_calloc(1, \
	ft_strlen(node->token) - calc_quote_and_escape(node->token) + 1);
	ft_assert(temp != NULL, "ERROR : leak resource in lexer()");
	temp[ft_strlen(node->token) - calc_quote_and_escape(node->token)] = '\0';
	remove_quote_and_escape(temp, node->token);
	free(node->token);
	node->token = temp;
}

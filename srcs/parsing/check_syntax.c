#include "libft.h"
#include "token.h"
#include <stdio.h>

int	syntax_check_pipe(t_tok *node, int *cmd_flag)
{
	if (node->type == TOK_TYPE_PIPE)
	{
		if (*cmd_flag == 0)
			return (-1);
		*cmd_flag = 0;
	}
	return (0);
}

void	syntax_check_cmd(t_tok *node, int *cmd_flag)
{
	if (node->type == TOK_TYPE_CMD)
		*cmd_flag = 1;
}

int	syntax_check_file(t_tok *node)
{
	if (node->type == TOK_TYPE_FILE && node->token[0] == '|')
		return (-1);
	return (0);
}

int	check_syntax(t_tok_list *list)
{
	int		cmd_flag;
	int		cnt;
	t_tok	*iter;

	cmd_flag = 0;
	cnt = -1;
	iter = list->head;
	while (++cnt < list->size)
	{
		if (syntax_check_pipe(iter, &cmd_flag))
			return (-1);
		if (syntax_check_file(iter))
			return (-1);
		syntax_check_cmd(iter, &cmd_flag);
		iter = iter->next;
	}
	return (0);
}

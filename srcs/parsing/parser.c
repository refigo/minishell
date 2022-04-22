#include "minishell.h"

t_ast	*parser(t_info *info, char *input)
{
	t_tok	*iter;
	t_ast	*node;
	t_ast	*trunk;
	int		cnt;

	info->tok_list = tokenizer(input);
	if (lexer(info->tok_list) == -1)
		return (NULL);
	iter = info->tok_list->head;
	trunk = NULL;
	cnt = 0;
	while (cnt < info->tok_list->size)
	{
		node = new_ast(iter);
		trunk = ast_insert(trunk, node);
		iter = iter->next;
		++cnt;
	}
	info->syntax = trunk;
	return (trunk);
}

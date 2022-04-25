#include "minishell.h"

t_ast	*parser(t_info *info)
{
	t_tok	*iter;
	t_ast	*node;
	t_ast	*trunk;
	int		cnt;

	search_var(&(info->input), info->unordered_env, false);
	if (info->input == NULL)
		return (NULL);
	info->tok_list = tokenizer(info->input);
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

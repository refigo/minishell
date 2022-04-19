#include "libft.h"
#include "token.h"
#include "ast.h"

t_ast	*parser(t_tok_list *list)
{
	t_tok	*iter;
	t_ast	*node;
	t_ast	*trunk;
	int		cnt;

	iter = list->head;
	trunk = NULL;
	cnt = 0;
	while (cnt < list->size)
	{
		node = new_ast(iter);
		trunk = ast_insert(trunk, node);
		iter = iter->next;
		++cnt;
	}
	return (trunk);
}

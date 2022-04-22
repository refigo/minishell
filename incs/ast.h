#ifndef AST_H
# define AST_H

# include "token.h"

typedef struct s_ast
{
	char			*token;
	t_tok_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}					t_ast;

t_ast	*new_ast(t_tok *token);
t_ast	*ast_insert(t_ast *trunk, t_ast *node);
void	ast_free(t_ast **ast);

#endif

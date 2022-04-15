
#ifndef AST_H
# define AST_H

# include "token.h"

typedef struct s_ast
{
	//bool			root;
	char			*token;
	t_tok_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif
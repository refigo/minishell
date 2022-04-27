/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:40:27 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:40:30 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

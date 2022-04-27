/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:34 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 19:58:17 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "ast.h"

t_ast	*ast_insert_lt(t_ast *trunk, t_ast *node)
{
	t_ast	*temp;

	temp = trunk->parent;
	trunk->parent = node;
	node->parent = temp;
	node->right = trunk;
	return (node);
}

t_ast	*ast_insert_eq(t_ast *trunk, t_ast *node)
{
	t_ast	*temp;

	if (node->type == TOK_TYPE_PIPE)
	{
		temp = trunk->parent;
		trunk->parent = node;
		node->parent = temp;
		node->right = trunk;
		return (node);
	}
	node->parent = trunk;
	trunk->right = ast_insert(trunk->right, node);
	return (trunk);
}

t_ast	*ast_insert_gt(t_ast *trunk, t_ast *node)
{
	node->parent = trunk;
	if (trunk->type == TOK_TYPE_REDIR \
		&& node->type == TOK_TYPE_FILE && trunk->left == NULL)
	{
		trunk->left = ast_insert(trunk->left, node);
		return (trunk);
	}
	else if (trunk->type == TOK_TYPE_PIPE)
	{
		if (trunk->right == NULL)
			trunk->right = ast_insert(trunk->right, node);
		else
			trunk->left = ast_insert(trunk->left, node);
	}
	else
		trunk->right = ast_insert(trunk->right, node);
	return (trunk);
}

t_ast	*ast_insert(t_ast *trunk, t_ast *node)
{
	if (trunk == NULL)
		return (node);
	if (node->type < trunk->type)
		trunk = ast_insert_lt(trunk, node);
	else if (node->type == trunk->type)
		trunk = ast_insert_eq(trunk, node);
	else
		trunk = ast_insert_gt(trunk, node);
	return (trunk);
}

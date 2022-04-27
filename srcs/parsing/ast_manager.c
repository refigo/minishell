/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:37 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:53:05 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "ast.h"

t_ast	*new_ast(t_tok *token)
{
	t_ast	*ret;
	char	*temp;

	if (token == NULL)
		ft_assert(false, "ERROR : NULL in new_ast()");
	ret = malloc(sizeof(t_ast));
	ft_assert(ret != NULL, "ERROR : leak resource in new_ast()");
	temp = ft_strdup(token->token);
	ft_assert(temp != NULL, "ERROR : leak resource in new_ast()");
	ret->token = temp;
	ret->type = token->type;
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = NULL;
	return (ret);
}

void	ast_free(t_ast **ast)
{
	if ((*ast)->right != NULL)
		ast_free(&((*ast)->right));
	if ((*ast)->left != NULL)
		ast_free(&((*ast)->left));
	free((*ast)->token);
	ft_free((void **)ast);
}

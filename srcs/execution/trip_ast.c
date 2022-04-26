/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trip_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:27:28 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 11:27:30 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new_cmd_area(t_cmda_list **cmd_areas, t_cmda_list *new)
{
	t_cmda_list	*tmp;

	ft_assert(cmd_areas != NULL && new != NULL, \
		"null guard activated in add_new_cmd_area");
	if (*cmd_areas == NULL)
		*cmd_areas = new;
	else
	{
		tmp = *cmd_areas;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	trip_and_set_cmd_area(t_exec_data *data, t_ast *node)
{
	t_cmda_list	*new_cmd_area;

	ft_assert(node->type == TOK_TYPE_REDIR || node->type == TOK_TYPE_CMD, \
		"type error in trip_and_set_cmd_area");
	new_cmd_area = ft_calloc(1, sizeof(t_cmda_list));
	ft_assert(new_cmd_area != NULL, "malloc failed in trip_and_set_cmd_area");
	if (node->type == TOK_TYPE_REDIR)
		trip_and_set_redir(data, node, new_cmd_area);
	else if (node->type == TOK_TYPE_CMD)
		set_exec_and_cmd_args(data, node, new_cmd_area);
	add_new_cmd_area(&(data->cmd_areas), new_cmd_area);
}

void	trip_pipe(t_exec_data *data, t_ast *node)
{
	enum e_tok_type	right_type;

	ft_assert(node->type == TOK_TYPE_PIPE, \
		"no pipe type error in trip_pipe");
	data->num_pipes += 1;
	right_type = node->right->type;
	if (right_type == TOK_TYPE_PIPE)
		trip_pipe(data, node->right);
	else if (right_type == TOK_TYPE_REDIR || right_type == TOK_TYPE_CMD)
		trip_and_set_cmd_area(data, node->right);
	else
		ft_assert(FALSE, "right type error in trip_pipe");
	if (node->left->type == TOK_TYPE_REDIR || node->left->type == TOK_TYPE_CMD)
		trip_and_set_cmd_area(data, node->left);
	else
		ft_assert(FALSE, "left type error in trip_pipe");
}

void	trip_ast_with_setting_data(t_exec_data *data, t_ast *root)
{
	enum e_tok_type	type;

	type = root->type;
	if (type == TOK_TYPE_PIPE)
		trip_pipe(data, root);
	else if (type == TOK_TYPE_REDIR || type == TOK_TYPE_CMD)
		trip_and_set_cmd_area(data, root);
	else
		ft_assert(FALSE, "type error in trip_ast_with_setting_data");
}

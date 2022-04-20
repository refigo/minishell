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

int	trip_and_set_redir(t_exec_data *data, t_ast *node, t_cmda_list *cmd_area)
{
	t_redir_list	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir_list));
	if (new_redir == NULL)
	{
		// todo: modify this error handling
		printf("new_redir == NULL in trip_and_set_cmd_area\n");
		exit(1);
	}

	if (node->left == NULL || node->left->type != TOK_TYPE_FILE) // is limiter type_file too?
	{
		// todo: modify this error handling
		printf("node->left->type != TOK_TYPE_FILE in trip_and_set_cmd_area\n");
		exit(1);
	}

	// set redir
	// todo: refactor to compress code
	if (ft_strncmp(node->token, "<", 2) == 0)
	{
		new_redir->file_name = ft_strdup(node->left->token);
		new_redir->type = REDIR_IN;
	}
	else if (ft_strncmp(node->token, ">", 2) == 0)
	{
		new_redir->file_name = ft_strdup(node->left->token);
		new_redir->type = REDIR_OUT;
	}
	else if (ft_strncmp(node->token, "<<", 3) == 0)
	{
		// todo: with getting inputs
		new_redir->limiter = ft_strdup(node->left->token);
		new_redir->type = REDIR_IN_HEREDOC;
		data->num_heredoc += 1;
	}
	else if (ft_strncmp(node->token, ">>", 3) == 0)
	{
		new_redir->file_name = ft_strdup(node->left->token);
		new_redir->type = REDIR_OUT_APPEND;
	}

	add_new_redir(&(cmd_area->redirs), new_redir);

	if (node->right->type == TOK_TYPE_REDIR)
		trip_and_set_redir(data, node->right, cmd_area);
	else if (node->right->type == TOK_TYPE_CMD)
		set_exec_and_cmd_args(data, node->right, cmd_area);
	// todo: error when not cmd ?

	return (TRUE);
}

int	trip_and_set_cmd_area(t_exec_data *data, t_ast *node)
{
	t_cmda_list	*new_cmd_area;

	new_cmd_area = ft_calloc(1, sizeof(t_cmda_list));
	if (new_cmd_area == NULL)
	{
		// todo: modify this error handling
		printf("cmd_area == NULL in trip_and_set_cmd_area\n");
		exit(1);
	}
	if (node->type == TOK_TYPE_REDIR)
		trip_and_set_redir(data, node, new_cmd_area);
	else if (node->type == TOK_TYPE_CMD)
		set_exec_and_cmd_args(data, node, new_cmd_area);
	add_new_cmd_area(&(data->cmd_areas), new_cmd_area);
	return (SUCCESS);
}

int	trip_pipe(t_exec_data *data, t_ast *node)
{
	enum e_tok_type	right_type;

	right_type = node->right->type;
	data->num_pipes += 1;
	if (right_type == TOK_TYPE_PIPE)
		trip_pipe(data, node->right);
	else if (right_type == TOK_TYPE_REDIR || right_type == TOK_TYPE_CMD)
		trip_and_set_cmd_area(data, node->right);
	// todo: error when not cmd ?

	if (node->left->type == TOK_TYPE_REDIR || node->left->type == TOK_TYPE_CMD)
		trip_and_set_cmd_area(data, node->left);
	// todo: error when not cmd ?

	return (SUCCESS);
}

int	trip_ast_with_setting_data(t_exec_data *data, t_ast *root)
{
	enum e_tok_type	type;

	type = root->type;
	if (type == TOK_TYPE_PIPE)
		trip_pipe(data, root);
	else if (type == TOK_TYPE_REDIR || type == TOK_TYPE_CMD)
		trip_and_set_cmd_area(data, root);

	// todo: when not cmd
	return (SUCCESS);
}

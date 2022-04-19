/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:20:31 by mgo               #+#    #+#             */
/*   Updated: 2022/04/15 20:22:02 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	trip ast with saving data
	set pipe and fork cmd proc
	set redirs
	exec cmd
*/

int	add_new_cmd_place(t_cmd_list **cmd_places, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	if (cmd_places == NULL || new == NULL)
	{
		printf("cmd_places == NULL || new == NULL in add_new_redir\n");
		exit(1);
	}
	if (*cmd_places == NULL)
		*cmd_places = new;
	else
	{
		tmp = *cmd_places;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (TRUE);
}

int	add_new_redir(t_redir_list **redirs, t_redir_list *new)
{
	t_redir_list	*tmp;

	if (redirs == NULL || new == NULL)
	{
		printf("redirs == NULL || new == NULL in add_new_redir\n");
		exit(1);
	}
	if (*redirs == NULL)
		*redirs = new;
	else
	{
		tmp = *redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (TRUE);
}

int	set_cmd_and_args(t_tmp_data *data, t_ast *node, t_cmd_list *cmd_place)
{
	(void)data;
	(void)node;
	(void)cmd_place;
	return (TRUE);
}

int	trip_and_set_redir(t_tmp_data *data, t_ast *node, t_cmd_list *cmd_place)
{
	t_redir_list	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir_list));
	if (new_redir == NULL)
	{
		printf("new_redir == NULL in trip_and_set_cmd_place\n");
		exit(1);
	}
	if (node->right || node->right->type != TOK_TYPE_FILE)
	{
		printf("node->right->type != TOK_TYPE_FILE in trip_and_set_cmd_place\n");
		exit(1);
	}

	// set redir
	if (ft_strncmp(node->token, "<", 2))
	{
		new_redir->file_name = ft_strdup(node->right->token);
		new_redir->type = REDIR_IN;
	}
	else if (ft_strncmp(node->token, ">", 2))
	{
		new_redir->file_name = ft_strdup(node->right->token);
		new_redir->type = REDIR_OUT;
	}
	else if (ft_strncmp(node->token, "<<", 2))
	{
	
		new_redir->limiter = ft_strdup(node->right->token);
		new_redir->type = REDIR_IN_HEREDOC;
		data->num_heredoc += 1;
	}
	else if (ft_strncmp(node->token, ">>", 2))
	{
		new_redir->file_name = ft_strdup(node->right->token);
		new_redir->type = REDIR_OUT_APPEND;	
	}
	add_new_redir(&(cmd_place->redirs), new_redir);

	if (node->right->type == TOK_TYPE_PIPE)
		trip_and_set_redir(data, node->right, cmd_place);
	else if (node->right->type == TOK_TYPE_CMD)
		set_cmd_and_args(data, node->right, cmd_place);

	return (TRUE);
}

int	trip_and_set_cmd_place(t_tmp_data *data, t_ast *node)
{
	t_cmd_list	*new_cmd_place;

	new_cmd_place = ft_calloc(1, sizeof(t_cmd_list));
	if (new_cmd_place == NULL)
	{
		printf("cmd_place == NULL in trip_and_set_cmd_place\n");
		exit(1);
	}
	if (node->type == TOK_TYPE_REDIR)
		trip_and_set_redir(data, node, new_cmd_place);
	else if (node->type == TOK_TYPE_CMD)
		set_cmd_and_args(data, node, new_cmd_place);
	add_new_cmd_place(&(data->cmd_places), new_cmd_place);
	return (TRUE);
}

int	trip_pipe(t_tmp_data *data, t_ast *node)
{
	if (node->right->type == TOK_TYPE_PIPE)
		trip_pipe(data, node->right);
	else
	{
		trip_and_set_cmd_place(data, node->right);
	}
	trip_and_set_cmd_place(data, node->left);
	return (TRUE);
}

int	trip_ast_with_saving_data(t_tmp_data *data, t_ast *root)
{
	if (root->type == TOK_TYPE_PIPE)
		trip_pipe(data, root);
	return (TRUE);
}

int	execute_ast(t_ast *root)
{
	t_tmp_data	data;
	//int	fd_saver[2];

	// should?
	//fd_saver[0] = dup(STDIN_FILENO);
	//fd_saver[1] = dup(STDOUT_FILENO);

	ft_memset(&data, 0, sizeof(data));
	trip_ast_with_saving_data(&data, root);
	//set_pipe_and_fork_cmd_proc();

	// come back to original
	//dup2(fd_saver[0], STDIN_FILENO);
	//dup2(fd_saver[1], STDOUT_FILENO);
	return (1);
}

int	main(void)
{
	//t_tok_list	*lst;
	//info
	t_ast		*root;

	root = NULL;
	printf("mgoshell: Hello world!\n");

	//set_ast_test();

	execute_ast(root);

	return (0);
}

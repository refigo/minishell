#include "minishell.h"

int	set_cmd_and_args(t_exec_data *data, t_ast *node, t_cmdp_list *cmd_place)
{
	char	*cmd;

	data->num_cmds += 1;
	if (node->type == TOK_TYPE_CMD)
		cmd = ft_strdup(node->token);
	// get path and set exec (need envp!!!)
	// set args(counting)

	return (TRUE);
}

int	trip_and_set_redir(t_exec_data *data, t_ast *node, t_cmdp_list *cmd_place)
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

int	trip_and_set_cmd_place(t_exec_data *data, t_ast *node)
{
	t_cmdp_list	*new_cmd_place;

	new_cmd_place = ft_calloc(1, sizeof(t_cmdp_list));
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
	return (SUCCESS);
}

int	trip_pipe(t_exec_data *data, t_ast *node)
{
	data->num_pipes += 1;
	if (node->right->type == TOK_TYPE_PIPE)
		trip_pipe(data, node->right);
	else
		trip_and_set_cmd_place(data, node->right);
	trip_and_set_cmd_place(data, node->left);
	return (SUCCESS);
}

int	trip_ast_with_saving_data(t_exec_data *data, t_ast *root)
{
	if (root->type == TOK_TYPE_PIPE)
		trip_pipe(data, root);
	else
		trip_and_set_cmd_place(data, root);
	return (SUCCESS);
}

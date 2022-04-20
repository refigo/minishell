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

static void	set_cmd_args(t_exec_data *data, t_cmda_list *cmd_area, t_ast *node)
{
	t_ast	*tmp;
	int		cnt;

	tmp = node;
	cnt = 0;
	while (tmp)
	{
		cnt++;
		tmp = tmp->right;
	}
	cmd_area->cmd_args = ft_calloc(cnt + 1, sizeof(char *));
	// todo: exception
	cnt = -1;
	tmp = node;
	while (tmp)
	{
		cmd_area->cmd_args[++cnt] = ft_strdup(tmp->token);
		// todo: exception
		tmp = tmp->right;
	}
}

static void	set_exec(t_exec_data *data, t_cmda_list *cmd_area, char **path)
{
	char	*cmd;
	int		i;

	cmd = cmd_area->exec;
	i = -1;
	while (path && path[++i])
	{
		cmd_area->exec = ft_strjoin(path[i], cmd);
		// todo: exception
		if (access(cmd_area->exec, X_OK) == SUCCESS)
			break ;
		free(cmd_area->exec);
		cmd_area->exec = NULL;
	}
	if (cmd_area->exec == NULL)
		cmd_area->exec = ft_strdup("cmd");
	// todo: exception
}

static void	add_slash_to_path(t_exec_data *data, char **path)
{
	char	*buf;
	int		len_path;
	int		i;

	if (path == NULL)
		return ;
	i = -1;
	while (path[++i])
	{
		len_path = ft_strlen(path[i]);
		buf = (char *)ft_calloc(1, len_path + 2);
		// todo: exception
		ft_memmove(buf, path[i], len_path);
		buf[len_path] = '/';
		free(path[i]);
		path[i] = buf;
	}
}

int	set_exec_and_cmd_args(t_exec_data *data, t_ast *node, t_cmda_list *cmd_area)
{
	t_info		*info_addr;
	t_env_node	*env_path;
	char		**path;

	info_addr = data->info;
	if (node->type != TOK_TYPE_CMD)
		return (FAIL); // todo: modify
	data->num_cmds += 1;
	cmd_area->exec = node->token;
	env_path = get_env_node(info_addr->unordered_env, "PATH");
	path = ft_split(env_path->value, ':'); // todo: exeception
	add_slash_to_path(data, path);
	set_exec(data, cmd_area, path);
	set_cmd_args(data, cmd_area, node);
	return (TRUE);
}

int	trip_and_set_redir(t_exec_data *data, t_ast *node, t_cmda_list *cmd_area)
{
	t_redir_list	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir_list));
	if (new_redir == NULL)
	{
		printf("new_redir == NULL in trip_and_set_cmd_area\n");
		exit(1);
	}
	if (node->right || node->right->type != TOK_TYPE_FILE)
	{
		printf("node->right->type != TOK_TYPE_FILE in trip_and_set_cmd_area\n");
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
	add_new_redir(&(cmd_area->redirs), new_redir);

	if (node->right->type == TOK_TYPE_PIPE)
		trip_and_set_redir(data, node->right, cmd_area);
	else if (node->right->type == TOK_TYPE_CMD)
		set_exec_and_cmd_args(data, node->right, cmd_area);

	return (TRUE);
}

int	trip_and_set_cmd_area(t_exec_data *data, t_ast *node)
{
	t_cmda_list	*new_cmd_area;

	new_cmd_area = ft_calloc(1, sizeof(t_cmda_list));
	if (new_cmd_area == NULL)
	{
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
	data->num_pipes += 1;
	if (node->right->type == TOK_TYPE_PIPE)
		trip_pipe(data, node->right);
	else
		trip_and_set_cmd_area(data, node->right);
	trip_and_set_cmd_area(data, node->left);
	return (SUCCESS);
}

int	trip_ast_with_saving_data(t_exec_data *data, t_ast *root)
{
	if (root->type == TOK_TYPE_PIPE)
		trip_pipe(data, root);
	else
		trip_and_set_cmd_area(data, root);
	// todo: not cmd
	return (SUCCESS);
}

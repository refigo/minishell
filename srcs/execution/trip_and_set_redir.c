/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trip_and_set_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:20:02 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 17:20:03 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_heredoc(t_exec_data *data, t_redir_list *redir)
{
	char	*index_str;
	int		ret_fd;

	index_str = ft_itoa(data->num_heredoc);	// todo: error handling
	redir->file_name = ft_strjoin(".heredoc", index_str);	// todo: error handling
	free(index_str);
	ret_fd = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);	// todo: error handling
	return (ret_fd);
}

static int	get_and_save_heredoc(t_exec_data *data, t_redir_list *redir, \
	char *limiter)
{
	int		fd_heredoc;
	char	*input_line;
	int		is_limiter;

	fd_heredoc = create_heredoc(data, redir); // todo: error handling
	is_limiter = FALSE;
	while (is_limiter == FALSE)
	{
		ft_putstr_fd("> ", 1);
		if (get_next_line(STDIN_FILENO, &input_line) == -1)
			exit(1);	// todo: modify this error handling
		if (ft_strncmp(input_line, limiter, ft_strlen(limiter) + 1) == 0) // todo: use macro num
			is_limiter = TRUE;
		if (is_limiter == FALSE)
			ft_putendl_fd(input_line, fd_heredoc);
		free(input_line);
	}
	close(fd_heredoc);
	return (SUCCESS);
}

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
	// todo: use macro in ft_strncmp?
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
		get_and_save_heredoc(data, new_redir, node->left->token);
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
	// todo: error when others ?

	return (TRUE);
}

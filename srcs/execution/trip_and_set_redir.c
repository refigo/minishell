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

	index_str = ft_itoa(data->num_heredoc);
	ft_assert(index_str != NULL, "ft_itoa failed in create_heredoc");
	redir->file_name = ft_strjoin(".heredoc", index_str);
	free(index_str);
	ft_assert(redir->file_name != NULL, "ft_strjoin failed in create_heredoc");
	ret_fd = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_assert(ret_fd != -1, "open failed in create_heredoc");
	return (ret_fd);
}

static void	set_and_save_heredoc(t_exec_data *data, t_redir_list *redir, \
	char *limiter)
{
	int		fd_heredoc;
	char	*input_line;
	int		is_limiter;

	fd_heredoc = create_heredoc(data, redir);
	is_limiter = FALSE;
	while (is_limiter == FALSE)
	{
		input_line = readline("> ");
		if (input_line == NULL)
			break ;
		if (ft_strncmp(input_line, limiter, ft_strlen(limiter) + 1) == 0)
			is_limiter = TRUE;
		if (is_limiter == FALSE)
			ft_putendl_fd(input_line, fd_heredoc);
		free(input_line);
	}
	close(fd_heredoc);
}

static void	set_redir(t_redir_list *redir, t_exec_data *data, t_ast *node)
{
	if (ft_strncmp(node->token, "<<", 3) == 0)
	{
		set_and_save_heredoc(data, redir, node->left->token);
		redir->type = REDIR_IN_HEREDOC;
		data->num_heredoc += 1;
	}
	else
	{
		redir->file_name = ft_strdup(node->left->token);
		if (ft_strncmp(node->token, "<", 2) == 0)
			redir->type = REDIR_IN;
		else if (ft_strncmp(node->token, ">", 2) == 0)
			redir->type = REDIR_OUT;
		else if (ft_strncmp(node->token, ">>", 3) == 0)
			redir->type = REDIR_OUT_APPEND;
	}
}

static void	add_new_redir(t_redir_list **redirs, t_redir_list *new)
{
	t_redir_list	*tmp;

	ft_assert(redirs != NULL && new != NULL, \
		"NULL guard activated in add_new_redir");
	if (*redirs == NULL)
		*redirs = new;
	else
	{
		tmp = *redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	trip_and_set_redir(t_exec_data *data, t_ast *node, \
	t_cmda_list *cmd_area)
{
	t_redir_list	*new_redir;

	ft_assert(node->left != NULL || node->left->type == TOK_TYPE_FILE, \
		"redir file format is wrong in trip_and_set_redir");
	new_redir = ft_calloc(1, sizeof(t_redir_list));
	ft_assert(new_redir != NULL, "malloc failed in trip_and_set_redir");
	set_redir(new_redir, data, node);
	add_new_redir(&(cmd_area->redirs), new_redir);
	if (node->right)
	{
		if (node->right->type == TOK_TYPE_REDIR)
			trip_and_set_redir(data, node->right, cmd_area);
		else if (node->right->type == TOK_TYPE_CMD)
			set_exec_and_cmd_args(data, node->right, cmd_area);
		else
			ft_assert(FALSE, \
				"type error at node of right in trip_and_set_redir");
	}
}

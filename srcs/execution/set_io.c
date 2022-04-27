/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:13:09 by mgo               #+#    #+#             */
/*   Updated: 2022/04/27 18:13:11 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_io_first(t_exec_data *data, int idx)
{
	int	stat;

	close_pipe_idx(data->pipes, idx, READ);
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);
	close_pipe_idx(data->pipes, idx, WRITE);
	ft_assert(stat != FAIL, "dup2 failed in set_io_first");
}

void	set_io_mid(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);
	close_pipe_idx(data->pipes, idx - 1, READ);
	ft_assert(stat != FAIL, "dup2 failed in set_io_mid");
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);
	close_pipe_idx(data->pipes, idx, WRITE);
	ft_assert(stat != FAIL, "dup2 failed in set_io_mid");
}

void	set_io_last(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);
	close_pipe_idx(data->pipes, idx - 1, READ);
	ft_assert(stat != FAIL, "dup2 failed in set_io_last");
}

void	set_io_on_redir(t_redir_list *redir)
{
	enum e_redir	type;
	int				fd;
	int				stat;

	type = redir->type;
	if (type == REDIR_IN || type == REDIR_IN_HEREDOC)
	{
		fd = open(redir->file_name, O_RDONLY);
		stat = dup2(fd, STDIN_FILENO);
	}
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
	{
		if (type == REDIR_OUT)
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (type == REDIR_OUT_APPEND)
			fd = open(redir->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		stat = dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	ft_assert(stat != FAIL, "dup2 failed in set_io_on_redir");
}

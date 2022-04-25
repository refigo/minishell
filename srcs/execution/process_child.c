/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:20:45 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 21:20:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_io_first(t_exec_data *data, int idx)
{
	int	stat;

	close_pipe_idx(data->pipes, idx, READ);
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);
	close_pipe_idx(data->pipes, idx, WRITE);
	ft_assert(stat != FAIL, "dup2 failed in set_io_first");
}

static void	set_io_mid(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);
	close_pipe_idx(data->pipes, idx - 1, READ);
	ft_assert(stat != FAIL, "dup2 failed in set_io_mid");
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);
	close_pipe_idx(data->pipes, idx, WRITE);
	ft_assert(stat != FAIL, "dup2 failed in set_io_mid");
}

static void	set_io_last(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);
	close_pipe_idx(data->pipes, idx - 1, READ);
	ft_assert(stat != FAIL, "dup2 failed in set_io_last");
}

static void	set_io_on_redir(t_redir_list *redir)
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

void	process_child(t_exec_data *data, t_cmda_list *cmda, int idx)
{
	t_redir_list	*tmp_redir;

	if (data->num_cmds != 1)
	{
		if (idx == 0)
			set_io_first(data, idx);
		else if (idx == data->num_cmds - 1)
			set_io_last(data, idx);
		else
			set_io_mid(data, idx);
	}
	tmp_redir = cmda->redirs;
	while (tmp_redir)
	{
		set_io_on_redir(tmp_redir);
		tmp_redir = tmp_redir->next;
	}
	if (execve(cmda->exec, cmda->cmd_args, ((t_info *)data->info)->envp) == -1)
	{
		ft_assert(access(cmda->exec, X_OK) == -1, \
			"execve failed in process_child");
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd((cmda->cmd_args)[0], 2);
		exit(127);	// todo: clearing data before exit
	}
}

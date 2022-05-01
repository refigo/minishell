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

int	set_io_on_redir(t_redir_list *redir)
{
	enum e_redir	type;
	int				fd;
	int				stat;

	fd = -1;
	type = redir->type;
	if (type == REDIR_IN || type == REDIR_IN_HEREDOC)
		fd = open(redir->file_name, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_OUT_APPEND)
		fd = open(redir->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		ft_assert(FALSE, "type error in set_io_on_redir");	
	if (fd == -1)
	{
		if (errno == ENOENT)
		{
			put_sh_cmd_name_for_error(redir->file_name);
			ft_putendl_fd(": No such file or directory", 2);
		}
		else if (errno == EACCES)
		{
			
			put_sh_cmd_name_for_error(redir->file_name);
			ft_putendl_fd(": Permission denied", 2);
		}
		else
			ft_putendl_fd("open failed in set_io_on_redir");
		return (FAIL);
	}
	// dup
	stat = FAIL;
	if (type == REDIR_IN || type == REDIR_IN_HEREDOC)
		stat = dup2(fd, STDIN_FILENO);
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
		stat = dup2(fd, STDOUT_FILENO);
	ft_assert(stat != FAIL, "dup2 failed in set_io_on_redir"); // to remove
	close(fd);
	return (SUCCESS);

/*
	fd = -1;
	stat = FAIL;
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
	else
		ft_assert(FALSE, "type error in set_io_on_redir");
	// 에러 발생 시키고 이후 redirection은 무시해야함
	// (자식 프로세스에서는 바로 종료시키면 되는데 부모 프로세스에서는 프롬프트로 나가야한다.)
	if (fd == -1)
	{
		put_sh_cmd_name_for_error(redir->file_name);
		ft_putendl_fd(": No such file or directory", 2);
		return (FAIL);
	}
	else
		close(fd);
	ft_assert(stat != FAIL, "dup2 failed in set_io_on_redir"); // to remove
	return (SUCCESS);
*/
}

int	set_io_on_redirs(t_cmda_list *cmda)
{
	t_redir_list	*tmp_redir;

	tmp_redir = cmda->redirs;
	while (tmp_redir)
	{
		if (set_io_on_redir(tmp_redir) == FAIL)
			return (FAIL);
		tmp_redir = tmp_redir->next;
	}
	return (SUCCESS);
}

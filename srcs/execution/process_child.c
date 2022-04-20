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
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx, WRITE);
}

static void	set_io_mid(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx - 1, READ);
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx, WRITE);
}

static void	set_io_last(t_exec_data *data, int idx)
{
	int	stat;
	
	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx - 1, READ);
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
	if (stat == FAIL)
		exit(1);	// todo: EH
}

void	process_child(t_exec_data *data, t_cmda_list *cmda, int idx)
{
	t_redir_list	*tmp_redir;
	t_info			*info;

	info = (t_info *)data->info;
	// todo: exception for only one cmd
	// set pipe
	if (idx == 0)
		set_io_first(data, idx);
	else if (idx == data->num_cmds - 1)
		set_io_last(data, idx);
	else
		set_io_mid(data, idx);
	
	// set redirs
	tmp_redir = cmda->redirs;
	while (tmp_redir)
	{
		set_io_on_redir(tmp_redir);
		tmp_redir = tmp_redir->next;
	}

	// execve
	if (execve(cmda->exec, cmda->cmd_args, info->envp) == -1)
	{
		if (access(cmda->exec, X_OK) == -1)
		{
			printf("mgosh: command not found: %s\n", (cmda->cmd_args)[0]);
			// todo: exit code 127
		}
		else
		{
			exit(1);	// todo: EH
			//exit_perror(data, 1);
		}
	}
}

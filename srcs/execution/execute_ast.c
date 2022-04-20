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

void	set_io_first(t_exec_data *data, int idx)
{
	int	stat;

	close_pipe_idx(data->pipes, idx, READ);
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx, WRITE);
}

void	set_io_mid(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx - 1, READ);
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx, WRITE);
}

void	set_io_last(t_exec_data *data, int idx)
{
	int	stat;
	
	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);	// todo: EH
	close_pipe_idx(data->pipes, idx - 1, READ);
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
	if (stat == FAIL)
		exit(1);	// todo: EH
}

void	process_child(t_exec_data *data, t_cmda_list *cmda, int idx)
{
	t_redir_list	*tmp_redir;
	t_info			*info;

	info = (t_info *)data->info;
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

void	process_parent(t_exec_data *data, int idx)
{
	if (idx == 0)
	{
		close_pipe_idx(data->pipes, idx, WRITE);
	}
	else if (idx == data->num_cmds - 1)
	{
		close_pipe_idx(data->pipes, idx - 1, READ);
	}
	else
	{
		close_pipe_idx(data->pipes, idx - 1, READ);
		close_pipe_idx(data->pipes, idx, WRITE);
	}
}

int	set_pipes_and_run_childs(t_exec_data *data)
{
	t_cmda_list	*turn;
	int			status_child;
	int			value_last_cmd;
	int			i;

	turn = data->cmd_areas;
	i = -1;
	while ((++i < data->num_cmds) && turn)
	{
		if (i < data->num_pipes)
			set_pipe_idx(data->pipes, i);	// todo: error handling
		data->pids[i] = fork();	// todo: error handling
		if (data->pids[i] == 0)
			process_child(data, turn, i);
		else
			process_parent(data, i);
		turn = turn->next;
	}
	// waitpid
	i = -1;
	while (++i < data->num_cmds)
		waitpid(data->pids[i], &status_child, 0);
	value_last_cmd = WEXITSTATUS(status_child);	// to use?
	return (SUCCESS);
}

int	execute_on_exec_data(t_exec_data *data)
{
	int	status_child;
	int	i;

	status_child = 0;
	calloc_pipes_and_pids(data);

	set_pipes_and_run_childs(data);	//set_pipe_and_fork_cmd_proc();

	return (SUCCESS);
}

/*
	trip ast with saving data [done implementation]
		pipe(recursively)
		cmd_place
			redir(recursively)
			cmd and args
	calloc pipes and pids
	execute on exec data
		set pipe and fork cmd proc
		set redirs
		exec cmd
	wait pids
	clear data
*/
int	execute_ast(t_info *info, t_ast *root)
{
	t_exec_data	data;
	int			fd_saver[2];

	ft_memset(&data, 0, sizeof(data));
	data.info = (void *)info;
	fd_saver[0] = dup(STDIN_FILENO);
	fd_saver[1] = dup(STDOUT_FILENO);

	trip_ast_with_setting_data(&data, root); // with setting_exec_data ?
	execute_on_exec_data(&data);

	//test_exec_data(&data);

	// clear_exec_data
	// unlink_heredocs

	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);

	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_on_exec_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:20:38 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 21:20:40 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_exec_data *data, t_cmda_list *cmda)
{
	int			ret_status;
	t_env_list	*env;
	char		*cmd_name;

	ret_status = 1;
	env = ((t_info *)data->info)->unordered_env;
	cmd_name = cmda->exec;
	if (mgo_strcmp(cmd_name, "echo") == 0)
		ret_status = builtin_echo(cmda->cmd_args);
	else if (mgo_strcmp(cmd_name, "cd") == 0)
		ret_status = builtin_cd(cmda->cmd_args, env);
	else if (mgo_strcmp(cmd_name, "pwd") == 0)
		ret_status = builtin_pwd();
	else if (mgo_strcmp(cmd_name, "export") == 0)
		ret_status = builtin_export(cmda->cmd_args, env);
	else if (mgo_strcmp(cmd_name, "unset") == 0)
		ret_status = builtin_unset(cmda->cmd_args, env);
	else if (mgo_strcmp(cmd_name, "env") == 0)
		ret_status = builtin_env(env);
	else if (mgo_strcmp(cmd_name, "exit") == 0)
		ret_status = builtin_exit(cmda->cmd_args);
	else
		ft_assert(FALSE, "builtin name error in exec_builtin");
	return (ret_status);
}

static void	process_child(t_exec_data *data, t_cmda_list *cmda, int idx)
{
	//t_redir_list	*tmp_redir;

	set_signal_in_cmd();
	if (data->num_cmdas != 1)
	{
		if (idx == 0)
			set_io_first(data, idx);
		else if (idx == data->num_cmdas - 1)
			set_io_last(data, idx);
		else
			set_io_mid(data, idx);
	}

	/*
	tmp_redir = cmda->redirs;
	while (tmp_redir)
	{
		set_io_on_redir(tmp_redir);
		tmp_redir = tmp_redir->next;
	}
	*/
	if (set_io_on_redirs(cmda) == FAIL)
		exit(1);

	if (cmda->exec == NULL)
		exit(0);
	if (cmda->is_builtin == TRUE)
		exit(exec_builtin(data, cmda));
	else if (ft_strchr(cmda->exec, '/') == NULL \
	&& get_env_node(((t_info *)data->info)->unordered_env, "PATH"))
		exit_error_not_found(cmda->cmd_args[0]);
	else if (execve(cmda->exec, cmda->cmd_args, \
		convert_env_char_d_ptr(((t_info *)data->info)->unordered_env)) == -1)
		exit_error_finding_not_executable(cmda);
}

static void	process_parent(t_exec_data *data, int idx)
{
	if (data->num_pipes == 0)
		return ;
	if (idx == 0)
		close_pipe_idx(data->pipes, idx, WRITE);
	else if (idx == data->num_cmdas - 1)
		close_pipe_idx(data->pipes, idx - 1, READ);
	else
	{
		close_pipe_idx(data->pipes, idx - 1, READ);
		close_pipe_idx(data->pipes, idx, WRITE);
	}
}

static int	wait_and_get_status_exit(t_exec_data *data)
{
	int			status_child;
	int			status_exit;
	int			i;

	i = -1;
	while (++i < data->num_cmdas) // modify
		waitpid(data->pids[i], &status_child, 0);
	if (WIFEXITED(status_child))
		status_exit = WEXITSTATUS(status_child);
	else
	{
		status_exit = WTERMSIG(status_child);
		if (status_exit == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		status_exit = 128 + status_exit;
	}
	return (status_exit);
}

int	execute_on_exec_data(t_exec_data *data)
{
	t_cmda_list	*curr;
	int			ret_status_exit;
	int			i;

	if (data->num_cmdas == 1 && data->cmd_areas->is_builtin == TRUE)
	{
		if (set_io_on_redirs(data->cmd_areas) == FAIL)
			return (1);
		ret_status_exit = exec_builtin(data, data->cmd_areas);
		return (ret_status_exit);
	}
	curr = data->cmd_areas;
	i = -1;
	while ((++i < data->num_cmdas) && curr)
	{
		if (i < data->num_pipes)
			set_pipe_idx(data->pipes, i);
		data->pids[i] = fork();
		ft_assert(data->pids[i] != -1, "fork failed in execute_on_exec_data");
		if (data->pids[i] == 0)
			process_child(data, curr, i);
		else
			process_parent(data, i);
		curr = curr->next;
	}
	ret_status_exit = wait_and_get_status_exit(data);
	return (ret_status_exit);
}

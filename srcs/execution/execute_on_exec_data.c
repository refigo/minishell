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

void	process_parent(t_exec_data *data, int idx)
{
	if (data->num_pipes == 0)
		return ;
	if (idx == 0)
		close_pipe_idx(data->pipes, idx, WRITE);
	else if (idx == data->num_cmds - 1)
		close_pipe_idx(data->pipes, idx - 1, READ);
	else
	{
		close_pipe_idx(data->pipes, idx - 1, READ);
		close_pipe_idx(data->pipes, idx, WRITE);
	}
}

int	execute_on_exec_data(t_exec_data *data)
{
	t_cmda_list	*curr;
	int			status_child;
	int			status_exit;
	int			i;

	curr = data->cmd_areas;
	i = -1;
	while ((++i < data->num_cmds) && curr)
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

	i = -1;
	while (++i < data->num_cmds)
		waitpid(data->pids[i], &status_child, 0);

	if (WIFEXITED(status_child))
		status_exit = WEXITSTATUS(status_child);	// to use?
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

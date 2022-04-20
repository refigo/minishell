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

int	execute_on_exec_data(t_exec_data *data)
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

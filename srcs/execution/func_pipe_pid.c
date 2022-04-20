/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipe_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:36:39 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:36:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calloc_pipes_and_pids(t_exec_data *data)
{
	data->pipes = ft_calloc(data->num_pipes * 2, sizeof(int));	// todo: error handling
	data->pids = ft_calloc(data->num_cmds, sizeof(pid_t));	// todo: error handling
	return (SUCCESS);
}

int	set_pipe_idx(int *pipes, int index)
{
	if (pipe(&(pipes[index * 2])) == -1)
		return (-1);
	return (0);
}

int	get_pipe_idx(int *pipes, int index, enum e_pipe ACT)
{
	return (pipes[(index * 2) + ACT]);
}

void	close_pipe_idx(int *pipes, int index, enum e_pipe ACT)
{
	close(pipes[(index * 2) + ACT]);
}

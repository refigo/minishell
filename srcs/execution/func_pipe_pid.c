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

void	calloc_pipes_and_pids(t_exec_data *data)
{
	if (data->num_pipes)
	{
		data->pipes = ft_calloc(data->num_pipes * 2, sizeof(int));
		ft_assert(data->pipes != NULL, "malloc failed at data->pipes");
	}
	if (data->num_cmds)
	{
		data->pids = ft_calloc(data->num_cmds, sizeof(pid_t));
		ft_assert(data->pids != NULL, "malloc failed at data->pids");
	}
}

void	set_pipe_idx(int *pipes, int index)
{
	int	check;

	check = pipe(&(pipes[index * 2]));
	ft_assert(check != FAIL, "pipe failed");
}

int	get_pipe_idx(int *pipes, int index, enum e_pipe ACT)
{
	return (pipes[(index * 2) + ACT]);
}

void	close_pipe_idx(int *pipes, int index, enum e_pipe ACT)
{
	close(pipes[(index * 2) + ACT]);
}

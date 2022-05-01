/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:19:46 by mgo               #+#    #+#             */
/*   Updated: 2022/05/01 19:19:50 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_io_pipe_first(t_exec_data *data, int idx)
{
	int	stat;

	close_pipe_idx(data->pipes, idx, READ);
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);
	close_pipe_idx(data->pipes, idx, WRITE);
	ft_assert(stat != FAIL, "dup2 failed in set_io_first");
}

static void	set_io_pipe_mid(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);
	close_pipe_idx(data->pipes, idx - 1, READ);
	ft_assert(stat != FAIL, "dup2 failed in set_io_mid");
	stat = dup2(get_pipe_idx(data->pipes, idx, WRITE), STDOUT_FILENO);
	close_pipe_idx(data->pipes, idx, WRITE);
	ft_assert(stat != FAIL, "dup2 failed in set_io_mid");
}

static void	set_io_pipe_last(t_exec_data *data, int idx)
{
	int	stat;

	stat = dup2(get_pipe_idx(data->pipes, idx - 1, READ), STDIN_FILENO);
	close_pipe_idx(data->pipes, idx - 1, READ);
	ft_assert(stat != FAIL, "dup2 failed in set_io_last");
}

void	set_io_pipe_in_order(t_exec_data *data, int idx)
{
	if (idx == 0)
		set_io_pipe_first(data, idx);
	else if (idx == data->num_cmdas - 1)
		set_io_pipe_last(data, idx);
	else
		set_io_pipe_mid(data, idx);
}

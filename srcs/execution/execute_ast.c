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

/*
	trip ast with saving data
		pipe(recursively)
		cmd_place
			redir(recursively)
			cmd and args
	calloc pipes and pids
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
	//set_pipe_and_fork_cmd_proc();

	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);

	test_exec_data(&data);

	// clear_exec_data
	return (SUCCESS);
}

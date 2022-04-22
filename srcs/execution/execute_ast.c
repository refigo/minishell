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
void	clear_exec_data()
{

}
*/

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
	trip_ast_with_setting_data(&data, root);
	calloc_pipes_and_pids(&data);
	execute_on_exec_data(&data);


	// clear_exec_data
	// with unlink_heredocs

	dup2(fd_saver[0], STDIN_FILENO);
	dup2(fd_saver[1], STDOUT_FILENO);

	return (SUCCESS);
}

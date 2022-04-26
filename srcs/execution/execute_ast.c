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

static void	clear_redirs(t_redir_list **redir)
{
	t_redir_list	*clearing;
	t_redir_list	*tmp;

	clearing = *redir;
	while (clearing)
	{
		if (clearing->type == REDIR_IN_HEREDOC)
			unlink(clearing->file_name);
		free(clearing->file_name);
		tmp = clearing->next;
		free(clearing);
		clearing = tmp;
	}
	*redir = NULL;
}

static void	clear_cmd_areas(t_cmda_list **cmda)
{
	t_cmda_list	*clearing;
	t_cmda_list	*tmp;

	clearing = *cmda;
	while (clearing)
	{
		free(clearing->exec);
		mgo_free_2ptr(clearing->cmd_args);
		clear_redirs(&(clearing->redirs));
		tmp = clearing->next;
		free(clearing);
		clearing = tmp;
	}
	*cmda = NULL;
}

void	clear_exec_data(t_exec_data *data)
{
	clear_cmd_areas(&(data->cmd_areas));
	free(data->pipes);
	free(data->pids);
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

	ft_memset(&data, 0, sizeof(data));
	data.info = (void *)info;
	trip_ast_with_setting_data(&data, root);
	calloc_pipes_and_pids(&data);

	signal(SIGINT, SIG_IGN);
	on_echoctl();
	execute_on_exec_data(&data);
	off_echoctl();

	clear_exec_data(&data);
	return (SUCCESS); // to remove ?
}

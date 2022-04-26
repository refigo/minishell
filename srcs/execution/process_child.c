/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:20:45 by mgo               #+#    #+#             */
/*   Updated: 2022/04/20 21:20:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_child(t_exec_data *data, t_cmda_list *cmda, int idx)
{
	t_redir_list	*tmp_redir;

	set_signal_in_cmd();
	if (data->num_cmds != 1)
	{
		if (idx == 0)
			set_io_first(data, idx);
		else if (idx == data->num_cmds - 1)
			set_io_last(data, idx);
		else
			set_io_mid(data, idx);
	}
	tmp_redir = cmda->redirs;
	while (tmp_redir)
	{
		set_io_on_redir(tmp_redir);
		tmp_redir = tmp_redir->next;
	}


// set is_builtin in set_cmda
	// check is_builtin
	

	if (execve(cmda->exec, cmda->cmd_args, \
		convert_env_char_d_ptr(((t_info *)data->info)->unordered_env)) == -1)
	{
		ft_assert(access(cmda->exec, X_OK) == -1, \
			"execve failed in process_child");
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((cmda->cmd_args)[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);	// todo: clearing data before exit
		// use errno
	}
}

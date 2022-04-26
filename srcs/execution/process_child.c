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
		builtin_exit(cmda->cmd_args);
	else
		ft_assert(FALSE, "builtin name error in exec_builtin");
	return (ret_status);
}

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

	if (cmda->is_builtin == TRUE)
		exec_builtin(data, cmda);
	else if (execve(cmda->exec, cmda->cmd_args, \
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
	exit(0); // consider: exit ?
}

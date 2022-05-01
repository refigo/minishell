/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:10:00 by mgo               #+#    #+#             */
/*   Updated: 2022/04/27 18:10:01 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "execution.h"

int	is_executable_bin(char *checking)
{
	struct stat	stat_buf;
	int			status;
	int			ret;

	ret = FALSE;
	status = lstat(checking, &stat_buf);
	if (status == 0 \
		&& ((stat_buf.st_mode & S_IFMT) == S_IFREG) \
		&& (stat_buf.st_mode & S_IXUSR))
		ret = TRUE;
	return (ret);
}

void	exit_error_finding_not_executable(t_cmda_list *cmda)
{
	struct stat	stat_buf;
	char		*exec_name;

	exec_name = cmda->exec;
	lstat(exec_name, &stat_buf);
	if (errno == ENOENT)
	{
		exit_error_noent(cmda->cmd_args[0]);
		exit(127);
	}
	else if (errno == EACCES)
	{
		if ((stat_buf.st_mode & S_IFMT) == S_IFDIR)
			exit_error_dir(cmda->cmd_args[0]);
		else
			exit_error_perm_denied(cmda->cmd_args[0]);
		exit(126);
	}
}

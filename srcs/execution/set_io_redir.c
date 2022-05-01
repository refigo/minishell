/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:19:57 by mgo               #+#    #+#             */
/*   Updated: 2022/05/01 19:20:00 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_fd_fail(t_redir_list *redir)
{
	if (errno == ENOENT)
		error_noent(redir->file_name);
	else if (errno == EACCES)
		error_perm_denied(redir->file_name);
	else
		ft_putendl_fd("open failed in set_io_on_redir", 2);
	return (FAIL);
}

static int	set_io_on_redir(t_redir_list *redir)
{
	enum e_redir	type;
	int				fd;
	int				stat;

	fd = FAIL;
	type = redir->type;
	if (type == REDIR_IN || type == REDIR_IN_HEREDOC)
		fd = open(redir->file_name, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_OUT_APPEND)
		fd = open(redir->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		ft_assert(FALSE, "type error in set_io_on_redir");
	if (fd == FAIL)
		return (error_fd_fail(redir));
	stat = FAIL;
	if (type == REDIR_IN || type == REDIR_IN_HEREDOC)
		stat = dup2(fd, STDIN_FILENO);
	else if (type == REDIR_OUT || type == REDIR_OUT_APPEND)
		stat = dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_assert(stat != FAIL, "dup2 failed in set_io_on_redir");
	return (SUCCESS);
}

int	set_io_on_redirs(t_cmda_list *cmda)
{
	t_redir_list	*tmp_redir;

	ft_assert(cmda != NULL, "cmda is NULL in set_io_on_redirs");
	tmp_redir = cmda->redirs;
	while (tmp_redir)
	{
		if (set_io_on_redir(tmp_redir) == FAIL)
			return (FAIL);
		tmp_redir = tmp_redir->next;
	}
	return (SUCCESS);
}

#include <sys/stat.h>
#include "execution.h"

#include <stdio.h>

#include "minishell.h"

/*
	lstat
		buf.st_mode
			S_ISREG
			S_ISDIR
			S_IXUSR
*/

// file? include also folder?
int	is_executable(char *checking)
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

// check_exec_errno

	// is a directory
	// Permission denied
	// No such file or directory

	// use errno
void	exit_with_finding_error(t_cmda_list *cmda)
{
	struct stat	stat_buf;
	char 		*exec_name;

	exec_name = cmda->exec;
	lstat(exec_name, &stat_buf);
	if (errno == ENOENT)
		exit_error_noent(cmda->cmd_args[0]);
	else if (errno == EACCES)
	{
		if ((stat_buf.st_mode & S_IFMT) == S_IFDIR)
			exit_error_dir(cmda->cmd_args[0]);
		else
			exit_error_perm_denied(cmda->cmd_args[0]);
	}
}

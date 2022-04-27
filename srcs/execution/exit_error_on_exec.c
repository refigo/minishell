#include <stdlib.h>
#include "libft.h"

void	put_sh_cmd_name_for_error(char *cmd_name)
{
	ft_putstr_fd("mbsh: ", 2);
	ft_putstr_fd(cmd_name, 2);
}

void	exit_error_not_found(char *cmd_name)
{
	put_sh_cmd_name_for_error(cmd_name);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	exit_error_noent(char *cmd_name)
{
	put_sh_cmd_name_for_error(cmd_name);
	ft_putendl_fd(": No such file or directory", 2);
	exit(127);
}

void	exit_error_dir(char *cmd_name)
{
	put_sh_cmd_name_for_error(cmd_name);
	ft_putendl_fd(": is a directory", 2);
	exit(126);
}

void	exit_error_perm_denied(char *cmd_name)
{
	put_sh_cmd_name_for_error(cmd_name);
	ft_putendl_fd(": Permission denied", 2);
	exit(126);
}

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	ft_putendl_fd(path, STDOUT_FILENO);
	ft_free((void **)(&path));
	return (0);
}

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	n_flag;

	n_flag = 0;
	if (*(args + 1) == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	if (mgo_strcmp("-n", *(args++)) != 0)
		n_flag = 1;
	args += n_flag;
	while (*args != NULL)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1) != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		++args;
	}
	if (n_flag == true)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

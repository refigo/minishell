#include "minishell.h"

static int	check_args(char **args)
{
	int		exit_code;
	char	*temp;

	exit_code = 0;
	temp = *(args + 1);
	while (temp != NULL && *temp)
		if (ft_isdigit(*(temp++)))
			return (255);
	if (exit_code == 0 && *(args + 1) != NULL && *(args + 2) != NULL)
		return (1);
	if (*(args + 1) == NULL)
		return (0);
	else
		return (ft_atoi(*(args + 1)));
}

void	builtin_exit(char **args)
{
	char	*e_msg[2];
	int			exit_code;
	char		*temp;

	e_msg[0] = "Numeric arguments required";
	e_msg[1] = "Too many arguments";
	exit_code = check_args(args);
	if (exit_code == 255)
	{
		ft_putstr_fd("exit\nexit: ", STDERR_FILENO);
		ft_putstr_fd(*(args + 1), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(e_msg[0], STDERR_FILENO);
		exit(exit_code);
	}
	else if (exit_code == 1)
	{
		ft_putstr_fd("exit\nexit: ", STDERR_FILENO);
		ft_putendl_fd(e_msg[1], STDERR_FILENO);
		exit(exit_code);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_code);
}

#include "minishell.h"

int	builtin_unset(char **args, t_env_list *env)
{
	int	exit_code;

	exit_code = 0;
	if (*(args + 1) == NULL)
		return (exit_code);
	while (*(++args) != NULL)
	{
		if (ft_isalpha(**args) == false)
		{
			exit_code = 1;
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(*args, STDERR_FILENO);
			ft_putendl_fd("': Not a valid identifier", STDERR_FILENO);
		}
		else
		{
			exit_code = 0;
			env_remove(env, *args);
		}
	}
	return (exit_code);
}
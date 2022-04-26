#include "minishell.h"

int	builtin_env(t_env_list *env)
{
	print_env(env, "%s=%s\n", "?");
	return (0);
}

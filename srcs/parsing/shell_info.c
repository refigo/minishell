#include "minishell.h"

int	init_info(t_info *info)
{
	if (info == NULL)
		return (-1);
	info->unordered_env = malloc(sizeof(t_env_list));
	ft_assert(info->unordered_env != NULL, \
	"ERROR : leak resource in init_info()");
	init_env_list(info->unordered_env);
	return (0);
}

void	free_info(t_info *info)
{
	del_env_list(&(info->unordered_env));
}

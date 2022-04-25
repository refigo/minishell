#include "minishell.h"

int	init_info(t_info *info)
{
	if (info == NULL)
		return (-1);
	info->unordered_env = malloc(sizeof(t_env_list));
	ft_assert(info->unordered_env != NULL, \
	"ERROR : leak resource in init_info()");
	init_env_list(info->unordered_env);
	info->tok_list = NULL;
	info->syntax = NULL;
	info->input = NULL;
	return (0);
}

void	free_info(t_info *info)
{
	if (info->unordered_env != NULL)
		del_env_list(&(info->unordered_env));
	if (info->tok_list != NULL)
		remove_token_list(&(info->tok_list));
	if (info->syntax != NULL)
		ast_free(&(info->syntax));

}

void	refresh_info(t_info *info)
{
	if (info->tok_list != NULL)
		remove_token_list(&(info->tok_list));
	if (info->syntax != NULL)
		ast_free(&(info->syntax));
	if (info->input != NULL)
		ft_free((void **)&(info->input));
}

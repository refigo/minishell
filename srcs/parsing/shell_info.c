/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:42:17 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:42:17 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (info->input != NULL)
		ft_free((void **)&(info->input));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:28 by bson              #+#    #+#             */
/*   Updated: 2022/04/29 16:26:32 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **args, t_env_list *env)
{
	int	exit_code;

	exit_code = 0;
	if (*(args + 1) == NULL)
		return (exit_code);
	while (*(++args) != NULL)
	{
		if (is_vaild_env(*args) == false)
		{
			exit_code = 1;
			ft_putstr_fd("mbsh: unset: `", STDERR_FILENO);
			ft_putstr_fd(*args, STDERR_FILENO);
			ft_putendl_fd("': Not a valid identifier", STDERR_FILENO);
		}
		else
		{
			exit_code = 0;
			env_remove(env, *args);
		}
	}
	return ((char)exit_code);
}

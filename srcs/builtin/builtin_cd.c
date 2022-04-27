/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:02 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:41:02 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_paths(char *old_path, char *new_path, int exit_code)
{
	ft_free((void **)&old_path);
	ft_free((void **)&new_path);
	return (exit_code);
}

int	builtin_cd(char **args, t_env_list *env)
{
	int		error_code;
	char	*old_path;
	char	*new_path;

	if (*(args + 1) == NULL)
		new_path = ft_strdup(get_env_value_not_malloc(env, "HOME"));
	else
		new_path = ft_strdup(*(args + 1));
	old_path = getcwd(NULL, 0);
	if (old_path == NULL || new_path == NULL)
		return (free_paths(old_path, new_path, 1));
	error_code = chdir(new_path);
	if (error_code < 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (free_paths(old_path, new_path, 1));
	}
	ft_free((void **)&new_path);
	env_insert(env, "OLDPWD", old_path);
	env_insert(env, "PWD", getcwd(NULL, 0));
	return (0);
}

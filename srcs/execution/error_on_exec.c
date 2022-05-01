/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_on_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:17:23 by mgo               #+#    #+#             */
/*   Updated: 2022/05/01 19:17:28 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	put_sh_name_for_error(char *name)
{
	ft_putstr_fd("mbsh: ", 2);
	ft_putstr_fd(name, 2);
}

void	exit_error_not_found(char *name)
{
	put_sh_name_for_error(name);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	error_noent(char *name)
{
	put_sh_name_for_error(name);
	ft_putendl_fd(": No such file or directory", 2);
}

void	error_dir(char *name)
{
	put_sh_name_for_error(name);
	ft_putendl_fd(": is a directory", 2);
}

void	error_perm_denied(char *name)
{
	put_sh_name_for_error(name);
	ft_putendl_fd(": Permission denied", 2);
}

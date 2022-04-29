/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:14 by bson              #+#    #+#             */
/*   Updated: 2022/04/29 14:15:10 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args(char **args)
{
	char	*temp;

	temp = *(args + 1);
	if (*temp == '-' || *temp == '+')
		++temp;
	while (temp != NULL && *temp)
		if (ft_isdigit(*(temp++)) == false)
			return (255);
	if (*(args + 1) != NULL && *(args + 2) != NULL)
		return (256);
	if (*(args + 1) == NULL)
		return (0);
	else
		return (ft_atoi(*(args + 1)));
}

int	builtin_exit(char **args)
{
	char	*e_msg[2];
	int		exit_code;

	e_msg[0] = "Numeric arguments required";
	e_msg[1] = "Too many arguments";
	exit_code = check_args(args);
	if (exit_code == 255)
	{
		ft_putstr_fd("exit\nmbsh: exit: ", STDERR_FILENO);
		ft_putstr_fd(*(args + 1), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(e_msg[0], STDERR_FILENO);
		exit(255);
	}
	else if (exit_code == 256)
	{
		ft_putstr_fd("exit\nmbsh: exit: ", STDERR_FILENO);
		ft_putendl_fd(e_msg[1], STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit((char)exit_code);
}

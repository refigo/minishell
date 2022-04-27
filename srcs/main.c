/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:11 by mgo               #+#    #+#             */
/*   Updated: 2022/04/27 19:57:56 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trash_arg(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

static int	exit_ctrl_d(void)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[6C", STDOUT_FILENO);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_ast		*syntax;

	trash_arg(argc, argv);
	init_info(&info);
	make_env_list(info.unordered_env, envp);
	while (true)
	{
		set_signal_in_prompt();
		off_echoctl();
		refresh_info(&info);
		info.input = readline("mbsh$ ");
		if (info.input == NULL)
			exit_ctrl_d();
		if (!ft_strlen(info.input) || is_empty(info.input))
			continue ;
		add_history(info.input);
		if (check_input(info.input) == false)
			continue ;
		syntax = parser(&info);
		if (syntax == NULL)
			continue ;
		execute_ast(&info, syntax);
	}
	return (0);
}

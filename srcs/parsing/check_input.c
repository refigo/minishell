/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:40 by bson              #+#    #+#             */
/*   Updated: 2022/04/29 00:48:33 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_check_error(char *input, char *message)
{
	ft_putstr_fd("mbsh: ", STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
}

static int	check_escape(char *input)
{
	char	*iter;

	iter = input;
	while (*iter)
	{
		if (*iter == '\\' && *(iter + 1) == '\0')
		{
			print_check_error(input, "unspecified special characters");
			return (false);
		}
		else if (*iter == '\"' && (iter == input || *(iter - 1) != '\\'))
			iter = jump_quotes(iter, '\"', false) + 1;
		else if (*iter == '\'' && (iter == input || *(iter - 1) != '\\'))
			iter = jump_quotes(iter, '\'', false) + 1;
		else
			++iter;
	}
	return (true);
}

static int	check_quote(char *input)
{
	char	*cmd;

	cmd = input;
	while (*cmd)
	{
		if (ft_strchr("\'\"", *cmd) && (cmd == input || *(cmd -1) != '\\'))
			cmd = jump_quotes(cmd, *cmd, false);
		if (cmd == NULL)
		{
			print_check_error(input, "Quotes not paired");
			return (false);
		}
		++cmd;
	}
	return (true);
}

int	is_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (!ft_isspace(input[i]))
			return (false);
	return (true);
}

int	check_input(char *input)
{
	if (check_quote(input) == false)
		return (false);
	if (check_escape(input) == false)
		return (false);
	return (true);
}

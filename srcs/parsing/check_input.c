#include "minishell.h"

static void	print_check_error(char *input, char *message)
{
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
		if (*iter == '\\' && (*(iter + 1) == '\0' || *(iter + 1) == ' '))
		{
			print_check_error(input, "unspecified special characters");
			return (false);
		}
		iter = jump_quotes(iter, *iter) + 1;
	}
	return (true);
}

static int	check_quote(char *input)
{
	char	*cmd;

	cmd = input;
	while (*cmd)
	{
		if (*cmd == '\"' && (cmd == input || *(cmd - 1) != '\\'))
			cmd = jump_quotes(cmd, '\"');
		if (cmd == NULL)
		{
			print_check_error(input, "Quotes not paired");
			return (false);
		}
		if (*cmd == '\'' && (input == cmd || *(cmd - 1) != '\\'))
			cmd = jump_quotes(cmd, '\'');
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

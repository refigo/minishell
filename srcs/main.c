#include "minishell.h"

#include <termios.h>
static void	off_echoctl()
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag = attr.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}


void	set_new_rl(int sig)
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_in_prompt()
{
	signal(SIGINT, set_new_rl);
	signal(SIGQUIT, SIG_IGN);
}

int main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_ast		*syntax;

	init_info(&info);
	make_env_list(info.unordered_env, argc, argv, envp);
	while (true)
	{
		set_signal_in_prompt();
		off_echoctl();

		refresh_info(&info);
		info.input = readline("minishell$ ");

		if (info.input == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}

		//ft_assert(info.input != NULL, "leak resource in main()");
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

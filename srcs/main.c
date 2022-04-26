#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_ast		*syntax;

	init_info(&info);
	make_env_list(info.unordered_env, argc, argv, envp);
	while (true)
	{
		// mgo
		set_signal_in_prompt(); // add: hadnling ctrl+C, ctrl+'\'
		off_echoctl(); // add: echo control

		refresh_info(&info);
		info.input = readline("minishell$ ");

		// mgo
		if (info.input == NULL)	// add: handling ctrl+D
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0); // consider: modify to clear?
		}
		//ft_assert(info.input != NULL, "leak resource in main()"); // to remove

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

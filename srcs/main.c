#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_tok_list	*token_list;
	t_ast		*syntax;
	char 		*temp;

	init_info(&info);
	info.envp = envp;	// mgo: set envp into info
	make_env_list(info.unordered_env, argc, argv, envp);
	while (true)
	{
		refresh_info(&info);
		info.input = readline("minishell$ ");
		ft_assert(info.input != NULL, "leak resource in main()");
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

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info		info;
	char		*input;
	t_tok_list	*token_list;
	t_ast		*syntax;
	char *temp;

	init_info(&info);
	info.envp = envp;	// mgo: set envp into info
	make_env_list(info.unordered_env, argc, argv, envp);
	/*
	{
		t_env_list	*sorted;
		sorted = env_sort_copy_env(info.unordered_env);
		printf("unordered env----------------------------\n");
		iter_env_list(info.unordered_env, print_node);
		printf("ordered env-------------------------------\n");
		iter_env_list(sorted, print_node);
		printf("-----------------------------------------\n");
		return (0);
	}
	*/
	while (true)
	{
		refresh_info(&info);
		input = readline("minishell$ ");
		if (!ft_strlen(input) || is_empty(input))
			continue ;
		add_history(input);
		check_quote(input);
		check_escape(input);
		search_var(&input, info.unordered_env, false);
		syntax = parser(&info, input);
		free(input);
		if (syntax == NULL)
			continue ;
		system("leaks minishell");
		execute_ast(&info, syntax); // mgo execution
		
	}


	return (0);
}

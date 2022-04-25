#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_tok_list	*token_list;
	t_ast		*syntax;
	char *temp;

	init_info(&info);
	info.envp = envp;	// mgo: set envp into info
	make_env_list(info.unordered_env, argc, argv, envp);
	// {
	// 	t_env_list	*sorted;
	// 	sorted = env_sort_copy_env(info.unordered_env);
	// 	printf("unordered env----------------------------\n");
	// 	iter_env_list(info.unordered_env, print_node);
	// 	printf("ordered env-------------------------------\n");
	// 	iter_env_list(sorted, print_node);
	// 	printf("-----------------------------------------\n");
	// 	return (0);
	// }
	// {
	// 	int i = -1;
	// 	char** my_envp;
	// 	printf("envp---------------------\n");
	// 	while (envp[++i] != NULL)
	// 		printf("<%d> %s\n", i, envp[i]);
	// 	my_envp = convert_env_char_d_ptr(info.unordered_env);
	// 	i = -1;
	// 	printf("my_envp***************************\n");
	// 	while (my_envp[++i] != NULL)
	// 		printf("<%d> %s\n", i, my_envp[i]);
	// 		system("leaks main.out");
	// 	return (0);
	// }
	while (true)
	{
		system("leaks minishell");
		refresh_info(&info);
		info.input = readline("minishell$ ");
		ft_assert(info.input != NULL, "leak resource in main()");
		if (!ft_strlen(info.input) || is_empty(info.input))
			continue ;
		add_history(info.input);
		if (check_input(info.input) == false)
			continue ;
		syntax = parser(&info, info.input);
		if (syntax == NULL)
			continue ;
		execute_ast(&info, syntax); // mgo execution

	}


	return (0);
}

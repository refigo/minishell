#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info		info;
	char		*input;
	t_tok_list	*token_list;
	t_ast		*syntax;
	char *temp;



	// {
	// 	int i = 0;

	// 	while (envp[i] != NULL)
	// 	{
	// 		printf("<%d> %s\n", i, envp[i]);
	// 		++i;
	// 	}
	// }
	init_info(&info);
	make_env_list(info.unordered_env, argc, argv, envp);
	input = readline("minishell$ ");
	if (!ft_strlen(input) || is_empty(input))
		printf("나중에 continue넣을곳\n");
	add_history(input);
	check_quote(input);
	check_escape(input);
	search_var(&input, info.unordered_env, false);
	//printf("%s\n", input);
	syntax = parser(&info, input);

	execute_ast(&info, syntax); // mgo execution

	return (0);
}

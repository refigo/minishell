#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "libft.h"
# include "env_manager.h"
# include "token.h"
# include "ast.h"

# include "exec_cmd.h" // mgo

typedef struct s_info
{
	t_env_list	*unordered_env;
}	t_info;

int		init_info(t_info *info);
void	free_info(t_info *info);
void	make_env_list(t_env_list *env, int argc, char **argv, char **envp);
int		check_quote(char *input);
int		is_empty(char *input);
void	search_var(char **input, t_env_list *env);
void	check_escape(char *input);
t_ast		*parser(t_tok_list *list);


#endif

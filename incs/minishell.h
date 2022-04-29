/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:40:44 by bson              #+#    #+#             */
/*   Updated: 2022/04/29 16:24:41 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "libft.h"
# include "env_manager.h"
# include "token.h"
# include "ast.h"

# include "execution.h" // mgo

typedef struct s_info
{
	t_env_list	*unordered_env;
	t_tok_list	*tok_list;
	t_ast		*syntax;
	char		*input;
}	t_info;

int		init_info(t_info *info);
void	free_info(t_info *info);
void	make_env_list(t_env_list *env, char **envp);
int		check_input(char *input);
int		is_empty(char *input);
void	search_var(char **input, t_env_list *env, bool quote_flag);
t_ast	*parser(t_info *info);
void	refresh_info(t_info *info);

// builtin
int		builtin_cd(char **args, t_env_list *env);
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_export(char **args, t_env_list *env);
int		builtin_unset(char **args, t_env_list *env);
int		builtin_env(t_env_list *env);
int		builtin_exit(char **args);
int		is_vaild_env(char *key);

// execution/execute_ast.c
void	execute_ast(t_info *info, t_ast *root);

// tool_func/handle_echoctl.c
void	on_echoctl(void);
void	off_echoctl(void);

// tool_func/handle_echoctl.c
void	set_signal_in_prompt(void);
void	set_signal_in_cmd(void);

#endif

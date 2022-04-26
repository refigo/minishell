/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:50 by mgo               #+#    #+#             */
/*   Updated: 2022/04/26 12:45:53 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include "ast.h"

enum e_bool // consider: move to minishell.h ?
{
	FALSE,
	TRUE
};

enum e_result // consider: move to minishell.h ?
{
	FAIL = -1,
	SUCCESS
};

enum	e_pipe
{
	READ,
	WRITE
};

enum e_redir
{
	REDIR_IN = 1,
	REDIR_OUT,
	REDIR_IN_HEREDOC,
	REDIR_OUT_APPEND
};

typedef struct s_redir_list
{
	char				*file_name;
	enum e_redir		type;

	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_cmda_list
{
	char				*exec;
	char				**cmd_args;
	struct s_redir_list	*redirs;

	struct s_cmda_list	*next;
}	t_cmda_list;

typedef struct s_exec_data
{
	int					num_cmds;
	int					num_pipes;
	int					num_heredoc;

	struct s_cmda_list	*cmd_areas;
	int					*pipes;
	pid_t				*pids;

	void				*info;
}	t_exec_data;

// trip_ast.c
int		trip_ast_with_setting_data(t_exec_data *data, t_ast *root);
void	trip_pipe(t_exec_data *data, t_ast *node);
void	trip_and_set_cmd_area(t_exec_data *data, t_ast *node);

// trip_and_set_redir.c
int		trip_and_set_redir(t_exec_data *data, t_ast *node, \
	t_cmda_list *cmd_area);

// set_exec_and_cmd_args.c
int		set_exec_and_cmd_args(t_exec_data *data, t_ast *node, \
	t_cmda_list *cmd_area);

// execute_on_exec_data.c
int		execute_on_exec_data(t_exec_data *data);

// process_child.c
void	process_child(t_exec_data *data, t_cmda_list *cmda, int idx);

// func_pipe_pid.c
int		calloc_pipes_and_pids(t_exec_data *data);
int		set_pipe_idx(int *pipes, int index);
int		get_pipe_idx(int *pipes, int index, enum e_pipe ACT);
void	close_pipe_idx(int *pipes, int index, enum e_pipe ACT);

// test_exec_data.c
void	test_exec_data(t_exec_data *data);

#endif
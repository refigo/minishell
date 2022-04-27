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

# include <errno.h>

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
	int					is_builtin;

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
void	trip_ast_with_setting_data(t_exec_data *data, t_ast *root);
void	trip_pipe(t_exec_data *data, t_ast *node);
void	trip_and_set_cmd_area(t_exec_data *data, t_ast *node);

// trip_and_set_redir.c
void	trip_and_set_redir(t_exec_data *data, t_ast *node, \
	t_cmda_list *cmd_area);

// set_exec_and_cmd_args.c
void	set_exec_and_cmd_args(t_exec_data *data, t_ast *node, \
	t_cmda_list *cmd_area);

// execute_on_exec_data.c
int		execute_on_exec_data(t_exec_data *data);

// set_io.c
void	set_io_first(t_exec_data *data, int idx);
void	set_io_mid(t_exec_data *data, int idx);
void	set_io_last(t_exec_data *data, int idx);
void	set_io_on_redir(t_redir_list *redir);

// executable.c // todo: rename find_file?
int		is_executable(char *checking);
void	exit_with_finding_error(t_cmda_list *cmda);

// exit_error_on_exec.c
void	put_sh_cmd_name_for_error(char *cmd_name);
void	exit_error_not_found(char *cmd_name);
void	exit_error_noent(char *cmd_name);
void	exit_error_dir(char *cmd_name);
void	exit_error_perm_denied(char *cmd_name);

// func_pipe_pid.c
void	calloc_pipes_and_pids(t_exec_data *data);
void	set_pipe_idx(int *pipes, int index);
int		get_pipe_idx(int *pipes, int index, enum e_pipe ACT);
void	close_pipe_idx(int *pipes, int index, enum e_pipe ACT);

#endif

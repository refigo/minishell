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
# include <errno.h>
# include "ast.h"

enum e_bool
{
	FALSE,
	TRUE
};

enum e_result
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
	int					num_cmdas;
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

// set_io_pipe.c
void	set_io_pipe_in_order(t_exec_data *data, int idx);

// set_io_redir.c
int		set_io_on_redirs(t_cmda_list *cmda);

// executable.c
int		is_executable_bin(char *checking);
void	exit_error_finding_not_executable(t_cmda_list *cmda);

// error_on_exec.c
void	put_sh_cmd_name_for_error(char *cmd_name);
void	exit_error_not_found(char *cmd_name);
void	error_noent(char *cmd_name);
void	error_dir(char *cmd_name);
void	error_perm_denied(char *cmd_name);

// pipe_pid.c
void	calloc_pipes_and_pids(t_exec_data *data);
void	set_pipe_idx(int *pipes, int index);
int		get_pipe_idx(int *pipes, int index, enum e_pipe ACT);
void	close_pipe_idx(int *pipes, int index, enum e_pipe ACT);

#endif

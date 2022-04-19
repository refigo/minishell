/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:18:36 by mgo               #+#    #+#             */
/*   Updated: 2022/04/19 20:18:40 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

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

enum e_redir
{
	REDIR_IN, 
	REDIR_OUT, 
	REDIR_IN_HEREDOC,
	REDIR_OUT_APPEND
};

typedef struct s_redir_list
{
	char				*file_name;
	enum e_redir		type;
	char				*limiter;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_cmdp_list
{
	char				*exec;
	char				**args;
	struct s_redir_list	*redirs;
	struct s_cmdp_list	*next;
}	t_cmdp_list;

typedef struct s_exec_data
{
	int					num_cmds;
	int					num_pipes;
	int					num_heredoc;
	struct s_cmdp_list	*cmd_places;
	int					*pipes;
	int					*pids;
}	t_exec_data;

#endif

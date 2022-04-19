
#ifndef EXEC_H
# define EXEC_H

struct s_redir_list
{
	char				*file_name;
	char				*type;	// considering to enum...
	struct s_redir_list	*next;
};

struct s_cmd_proc
{
	char				*exec;
	char				**args;
	struct s_redir_list	*redirs;
	struct s_cmd_proc	*next;
};

// temporary...
struct s_tmp_info
{
	int	num_heredoc;
	struct s_cmd_proc	*cmds;
};

#endif

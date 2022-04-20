#include <stdio.h>

#include "minishell.h"

static void	test_redir_list(t_redir_list *redirs)
{
	t_redir_list	*tmp_redir;

	tmp_redir = redirs;
	while (tmp_redir)
	{
		if (tmp_redir->type == REDIR_IN)
			printf("type: in\n");
		else if (tmp_redir->type == REDIR_OUT)
			printf("type: out\n");
		else if (tmp_redir->type == REDIR_IN_HEREDOC)
			printf("type: heredoc in\n");
		else if (tmp_redir->type == REDIR_OUT_APPEND)
			printf("type: append out\n");
		printf("file_name: [%s]\n", tmp_redir->file_name);
		tmp_redir = tmp_redir->next;
	}
}

static void	test_cmd_area_index(t_cmda_list *cmda, int idx)
{
	int	j;

	printf("----start test_cmd_area[%d]----\n", idx);

	printf("exec: [%s]\n", cmda->exec);

	printf("\n");
	
	printf("---cmd_args array\n");
	j = -1;
	while ((cmda->cmd_args)[++j])
		printf("[%s]\n", (cmda->cmd_args)[j]);
	printf("---end cmd_args\n");

	printf("\n");

	printf("---redirs\n");
	test_redir_list(cmda->redirs);
	printf("---done redirs\n");

	printf("\n");

	printf("----done test_cmd_area[%d]----\n", idx);
}

void	test_exec_data(t_exec_data *data)
{
	t_cmda_list	*tmp_cmda;
	int			i;

	printf("-----start test_exec_data-----\n");

	printf("data->num_cmds: [%d]\n", data->num_cmds);
	printf("num_pipes: [%d]\n", data->num_pipes);
	printf("num_heredoc: [%d]\n", data->num_heredoc);

	printf("\n");

	tmp_cmda = data->cmd_areas;
	i = -1;
	while (++i < (data->num_cmds))
	{
		test_cmd_area_index(tmp_cmda, i);
		tmp_cmda = tmp_cmda->next;
	}

	printf("\n");

	printf("-----done test_exec_data-----\n");
}
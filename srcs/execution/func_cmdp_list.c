#include "minishell.h"

int	add_new_cmd_place(t_cmdp_list **cmd_places, t_cmdp_list *new)
{
	t_cmdp_list	*tmp;

	if (cmd_places == NULL || new == NULL)
	{
		printf("cmd_places == NULL || new == NULL in add_new_redir\n");
		exit(1);
	}
	if (*cmd_places == NULL)
		*cmd_places = new;
	else
	{
		tmp = *cmd_places;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (TRUE);
}

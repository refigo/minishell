#include "minishell.h"

int	add_new_redir(t_redir_list **redirs, t_redir_list *new)
{
	t_redir_list	*tmp;

	if (redirs == NULL || new == NULL)
	{
		printf("redirs == NULL || new == NULL in add_new_redir\n");
		exit(1);
	}
	if (*redirs == NULL)
		*redirs = new;
	else
	{
		tmp = *redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (TRUE);
}

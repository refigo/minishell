#include "libft.h"
#include "env_manager.h"

void	env_remove_first(t_env_list *list)
{
	t_env_node	*temp;

	if (list->size == 0)
		return ;
	if (list->size == 1)
	{
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		temp = list->head;
		temp->next->prev = list->tail;
		list->head = temp->next;
		temp->prev->next = list->head;
		free(temp);
	}
	--(list->size);
}

void	env_remove_end(t_env_list *list)
{
	t_env_node	*temp;

	if (list->size == 0)
		return ;
	if (list->size == 1)
	{
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		temp = list->tail;
		temp->prev->next = list->head;
		list->tail = temp->prev;
		temp->next->prev = list->tail;
		free(temp);
	}
	--(list->size);
}

void	env_remove(t_env_list *list, char *key)
{
	t_env_node	*temp;
	int			cnt;

	if (list->size == 0)
		return ;
	if (list->size == 1)
	{
		env_remove_first(list);
		return ;
	}
	temp = get_env_node(list, key);
	if (temp == NULL)
		return ;
	if (list->head == temp || list->tail == temp)
	{
		if (list->head == temp)
			env_remove_first(list);
		else
			env_remove_end(list);
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp);
	--(list->size);
}

void	del_env_list(t_env_list **env_list)
{
	t_env_node	*iter;
	t_env_node	*iter_next;
	int			cnt;

	cnt = 0;
	iter = (*env_list)->head;
	while (cnt < (*env_list)->size)
	{
		iter_next = iter->next;
		free(iter);
		iter = iter_next;
		++cnt;
	}
	ft_free((void **)env_list);
}

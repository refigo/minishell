#include "libft.h"
#include "env_manager.h"

int	list_insert_first(t_env_list *list, t_env_node *node)
{
	t_env_node	*temp;

	if (list == NULL || node == NULL)
		return (-1);
	if (list->size == 0)
	{
		list->head = node;
		list->tail = node;
		node->prev = list->tail;
		node->next = list->head;
	}
	else
	{
		temp = list->head;
		list->head = node;
		node->prev = list->tail;
		node->next = temp;
		temp->prev = node;
	}
	++(list->size);
	return (0);
}

int	list_insert_end(t_env_list *list, t_env_node *node)
{
	t_env_node	*temp;

	if (list == NULL || node == NULL)
		return (-1);
	if (list->size == 0)
	{
		list->head = node;
		list->tail = node;
		node->prev = list->tail;
		node->next = list->head;
	}
	else
	{
		temp = list->tail;
		list->tail = node;
		node->prev = temp;
		node->next = list->head;
		temp->next = node;
	}
	++(list->size);
	return (0);
}

int	list_insert_mid(t_env_list *list, t_env_node *node, int n)
{
	t_env_node	*iter;
	t_env_node	*prev;

	if (list == NULL || node == NULL || n < 0 || n >= list->size)
		return (-1);
	if (n == 0)
		list_insert_first(list, node);
	else if (n == (list->size - 1))
		list_insert_end(list, node);
	iter = list->head;
	while (n--)
		iter = iter->next;
	prev = iter->prev;
	node->prev = prev;
	node->next = iter;
	prev->next = node;
	iter->prev = node;
	++(list->size);
	return (0);
}

int	list_insert_asc(t_env_list *list, t_env_node *node)
{
	int		idx;
	t_env_node	*iter;

	idx = 0;
	iter = list->head;
	if ((list->size == 0 || ft_strncmp(iter->key, node->key, BIG_SIZE) >= 0) \
		&& list_insert_first(list, node) == -1)
		return (-1);
	else if (ft_strncmp(list->tail->key, node->key, BIG_SIZE) < 0 && \
		list_insert_end(list, node) == -1)
		return (-1);
	else
	{
		while (ft_strncmp(iter->key, node->key, BIG_SIZE) < 0 && ++idx)
			iter = iter->next;
		if (ft_strncmp(iter->key, node->key, BIG_SIZE) == 0)
		{
			iter->value = node->value;
			free(node);
		}
		else if (list_insert_mid(list, node, idx) == -1)
			return (-1);
	}
	return (0);
}

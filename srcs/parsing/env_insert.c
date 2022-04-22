#include "libft.h"
#include "env_manager.h"

int	env_insert_first(t_env_list *list, t_env_node *node)
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
		list->tail->next = list->head;
		node->prev = list->tail;
		node->next = temp;
		temp->prev = node;
	}
	++(list->size);
	return (0);
}

int	env_insert_end(t_env_list *list, t_env_node *node)
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
		list->head->prev = list->tail;
		node->prev = temp;
		node->next = list->head;
		temp->next = node;
	}
	++(list->size);
	return (0);
}

int	env_insert_mid(t_env_list *list, t_env_node *node, int n)
{
	t_env_node	*iter;
	t_env_node	*prev;

	if (list == NULL || node == NULL || n < 0 || n >= list->size)
		return (-1);
	if (n == 0)
	{
		env_insert_first(list, node);
		return (0);
	}
	else if (n == list->size)
	{
		env_insert_end(list, node);
		return (0);
	}
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

int	env_insert_asc(t_env_list *list, t_env_node *node)
{
	int			idx;
	int			cnt;
	t_env_node	*iter;

	idx = 0;
	cnt = -1;
	iter = list->head;
	while (idx < list->size && ft_strncmp(iter->key, node->key, BIG_SIZE) < 0)
	{
		iter = iter->next;
		++idx;
	}
	if (ft_strncmp(iter->key, node->key, BIG_SIZE) == 0)
	{
		iter->value = node->value;
		free(node);
	}
	else if (env_insert_mid(list, node, idx) == 0)
		return (0);
	return (-1);
}

#include "libft.h"
#include "env_manager.h"

t_env_node	*new_node(char *key, char *value)
{
	t_env_node	*ret;

	ret = malloc(sizeof(t_env_node));
	ft_assert(ret != NULL, "ERROR : leak resource in new_node()");
	ret->key = key;
	ret->value = value;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

int	init_env_list(t_env_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (0);
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

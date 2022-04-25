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

t_env_node	*copy_node_unlink(t_env_node *node)
{
	return (new_node(node->key, node->value));
}

t_env_list	*env_sort_copy_env(t_env_list *list)
{
	t_env_list	*ret;
	t_env_node	*iter;
	int			cnt;

	ret = ft_calloc(1, sizeof(t_env_list));
	ft_assert(ret != NULL, "ERROR : leak resource in env_sort_copy_env()");
	cnt = -1;
	iter = list->head;
	while (++cnt < list->size)
	{
		env_insert_asc(ret, copy_node_unlink(iter));
		iter = iter->next;
	}
	return (ret);
}

int	init_env_list(t_env_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (0);
}

char	**convert_env_char_d_ptr(t_env_list *list)
{
	t_env_node	*iter;
	char		**ret;
	char		*temp;
	int			idx;

	ret = ft_calloc(list->size + 1, sizeof(char *));
	ft_assert(ret != NULL, "leak resource in convert_env...()");
	iter = list->head;
	idx = -1;
	while (++idx < list->size)
	{
		if (iter->key)
		temp = ft_strjoin(iter->key, "=");
		ret[idx] = ft_strjoin(temp, iter->value);
		ft_free((void **)&temp);
		iter = iter->next;
	}
	return (ret);
}

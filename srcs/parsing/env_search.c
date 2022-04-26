#include "libft.h"
#include "env_manager.h"

t_env_node	*get_env_node(t_env_list *list, char *key)
{
	t_env_node	*iter;
	int			cnt;

	if (list == NULL || key == NULL)
		return (NULL);
	iter = list->head;
	cnt = -1;
	while (++cnt < list->size && ft_strncmp(iter->key, key, BIG_SIZE) != 0)
			iter = iter->next;
	if (cnt == list->size)
		return (NULL);
	else
		return (iter);
}

char	*get_env_value_not_malloc(t_env_list *list, char *key)
{
	return (get_env_node(list, key)->value);
}

void	print_node(t_env_node *node)
{
	printf("key : %s | value : %s\n", node->key, node->value);
}

void	iter_env_list(t_env_list *list, void (*f)(t_env_node*))
{
	t_env_node	*iter;
	int			cnt;

	cnt = 0;
	iter = list->head;
	while (cnt < list->size)
	{
		f(iter);
		iter = iter->next;
		++cnt;
	}
}

void	env_modify_value_not_malloc(t_env_list *list, char *key, char *value)
{
	t_env_node	*modify_node;

	if (list == NULL || key == NULL || value == NULL)
		return ;
	modify_node = get_env_node(list, key);
	if (modify_node == NULL)
		return ;
	ft_free((void **)&(modify_node->value));
	modify_node->value = value;
}

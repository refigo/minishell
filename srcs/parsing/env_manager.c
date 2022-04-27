/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:54 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:41:55 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_manager.h"

t_env_node	*new_node(char *key, char *value)
{
	t_env_node	*ret;

	if (key == NULL || value == NULL)
		return (NULL);
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
	char	*m_key;
	char	*m_value;

	m_key = ft_strdup(node->key);
	m_value = ft_strdup(node->value);
	ft_assert(m_key != NULL && m_value != NULL, \
		"leak resource in copy_node_unlink()");
	return (new_node(m_key, m_value));
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

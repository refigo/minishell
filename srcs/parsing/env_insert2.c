/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:48 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:41:49 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_manager.h"

void	env_insert(t_env_list *list, char *key, char *value)
{
	t_env_node	*temp;

	if (list == NULL || key == NULL)
		return ;
	temp = get_env_node(list, key);
	if (temp == NULL)
	{
		if (value == NULL)
			temp = new_node(key, ft_strdup(""));
		else
			temp = new_node(key, value);
		env_insert_end(list, temp);
		return ;
	}
	else
	{
		if (value == NULL)
			return ;
		ft_free((void **)&(temp->value));
		temp->value = value;
		return ;
	}
}

void	env_insert_attach_value(t_env_list *list, char *key, char *value)
{
	t_env_node	*temp;
	char		*temp_value;

	if (list == NULL || key == NULL)
		return ;
	temp = get_env_node(list, key);
	if (temp == NULL)
	{
		if (value == NULL)
			temp = new_node(key, ft_strdup(""));
		else
			temp = new_node(key, value);
		env_insert_end(list, temp);
		return ;
	}
	else
	{
		if (value == NULL)
			return ;
		temp_value = ft_strjoin(temp->value, value);
		ft_free((void **)&(temp->value));
		temp->value = temp_value;
		return ;
	}
}

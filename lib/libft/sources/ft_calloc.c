/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:41:22 by mgo               #+#    #+#             */
/*   Updated: 2021/05/14 10:35:24 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*allocated;
	unsigned int	i;

	allocated = (char *)malloc(count * size);
	if (!allocated)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		allocated[i] = 0;
		i++;
	}
	return ((void *)allocated);
}

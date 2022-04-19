/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:12:21 by bson              #+#    #+#             */
/*   Updated: 2022/01/13 16:15:34 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int count)
{
	size_t	idx;
	char	*temp;

	if (count < 0)
		return (NULL);
	idx = 0;
	temp = malloc(count + 1);
	if (!temp)
		return (NULL);
	while (idx < count)
	{
		temp[idx] = s1[idx];
		idx++;
	}
	temp[count] = '\0';
	return (temp);
}

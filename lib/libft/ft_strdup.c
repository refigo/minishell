/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:41:26 by bson              #+#    #+#             */
/*   Updated: 2022/04/12 00:14:34 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	length;
	size_t	idx;
	char	*temp;

	if (s1 == NULL)
		return (NULL);
	idx = 0;
	length = ft_strlen(s1);
	temp = malloc(length + 1);
	if (!temp)
		return (NULL);
	while (s1[idx])
	{
		temp[idx] = s1[idx];
		idx++;
	}
	temp[length] = '\0';
	return (temp);
}

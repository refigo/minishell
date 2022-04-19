/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:29:35 by bson              #+#    #+#             */
/*   Updated: 2022/01/13 16:16:35 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	length;
	size_t	idx;
	char	*result;

	if (s == NULL || f == NULL)
		return (NULL);
	length = ft_strlen(s);
	idx = 0;
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	while (idx < length)
	{
		result[idx] = f(idx, s[idx]);
		idx++;
	}
	result[idx] = '\0';
	return (result);
}

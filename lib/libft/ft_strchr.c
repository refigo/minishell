/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:14:26 by bson              #+#    #+#             */
/*   Updated: 2022/01/19 10:44:25 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*(const unsigned char *)s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*(const unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

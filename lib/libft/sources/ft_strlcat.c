/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:37:29 by mgo               #+#    #+#             */
/*   Updated: 2021/05/14 13:50:15 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	while ((i < destsize) && (*dest != '\0'))
	{
		dest++;
		i++;
	}
	while ((i + 1 < destsize) && (*src != '\0'))
	{
		*(dest++) = *(src++);
		i++;
	}
	if (i < destsize)
		*dest = '\0';
	while (*src != '\0')
	{
		src++;
		i++;
	}
	return (i);
}

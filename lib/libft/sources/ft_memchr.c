/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 13:53:06 by mgo               #+#    #+#             */
/*   Updated: 2021/05/19 12:09:02 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*uc_s;

	uc_s = (const unsigned char *)s;
	while (n--)
	{
		if (*uc_s == (unsigned char)c)
			return ((void *)uc_s);
		uc_s++;
	}
	return (NULL);
}

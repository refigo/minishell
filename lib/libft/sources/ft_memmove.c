/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 13:45:28 by mgo               #+#    #+#             */
/*   Updated: 2021/05/19 12:02:35 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*uc_dest;
	unsigned char	*uc_src;

	uc_dest = (unsigned char *)dest;
	uc_src = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		while (len)
		{
			uc_dest[len - 1] = uc_src[len - 1];
			len--;
		}
	}
	else
	{
		while (len)
		{
			*(uc_dest++) = *(uc_src++);
			len--;
		}
	}
	return (dest);
}

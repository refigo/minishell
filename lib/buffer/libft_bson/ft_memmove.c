/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:45:11 by bson              #+#    #+#             */
/*   Updated: 2021/05/12 12:43:38 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	cast_dst = dst;
	cast_src = src;
	if (cast_dst <= cast_src)
		while (len--)
			*cast_dst++ = *cast_src++;
	else
	{
		cast_dst += (len - 1);
		cast_src += (len - 1);
		while (len--)
			*cast_dst-- = *cast_src--;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:55:42 by bson              #+#    #+#             */
/*   Updated: 2021/05/12 12:30:02 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	cast_dst = dst;
	cast_src = src;
	while (n--)
		*cast_dst++ = *cast_src++;
	return (dst);
}

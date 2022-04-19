/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:38:39 by bson              #+#    #+#             */
/*   Updated: 2021/05/12 13:20:08 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*cast_dst;
	const unsigned char	*cast_src;
	size_t				i;

	cast_dst = dst;
	cast_src = src;
	i = 0;
	while (n--)
	{
		cast_dst[i] = cast_src[i];
		if (cast_dst[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:50:16 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:50:17 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t count)
{
	size_t	dst_idx;
	size_t	src_idx;

	src_idx = 0;
	dst_idx = 0;
	while (dst[dst_idx])
		dst_idx++;
	while (count--)
	{
		dst[dst_idx] = src[src_idx];
		if (!dst[dst_idx])
			break ;
		dst_idx++;
		src_idx++;
	}
	dst[dst_idx] = '\0';
	return (dst);
}

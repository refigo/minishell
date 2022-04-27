/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:50:59 by bson              #+#    #+#             */
/*   Updated: 2022/04/27 18:50:59 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t count)
{
	size_t	dst_idx;
	size_t	src_idx;

	dst_idx = 0;
	src_idx = 0;
	while (count--)
	{
		dst[dst_idx] = src[src_idx];
		if (src[src_idx])
			src_idx++;
		dst_idx++;
	}
	return (dst);
}

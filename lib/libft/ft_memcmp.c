/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:22:23 by bson              #+#    #+#             */
/*   Updated: 2021/05/11 20:04:33 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cast_s1;
	const unsigned char	*cast_s2;

	cast_s1 = (const unsigned char *)s1;
	cast_s2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*cast_s1 != *cast_s2)
			return (*cast_s1 - *cast_s2);
		cast_s1++;
		cast_s2++;
	}
	return (0);
}

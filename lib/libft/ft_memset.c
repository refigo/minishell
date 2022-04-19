/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:58:38 by bson              #+#    #+#             */
/*   Updated: 2021/05/11 19:56:16 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cast_b;
	unsigned char	cast_c;

	cast_b = b;
	cast_c = c;
	while (len--)
	{
		*cast_b = cast_c;
		cast_b++;
	}
	return (b);
}

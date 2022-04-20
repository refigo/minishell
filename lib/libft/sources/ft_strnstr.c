/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:03:11 by mgo               #+#    #+#             */
/*   Updated: 2021/05/14 15:56:25 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	while ((*haystack) && len && ((len - needle_len + 1) > 0))
	{
		if (*haystack == *needle)
			if (!(ft_memcmp(haystack, needle, needle_len)))
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

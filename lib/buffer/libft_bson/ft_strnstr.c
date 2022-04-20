/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:15:05 by bson              #+#    #+#             */
/*   Updated: 2021/05/14 18:27:51 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		needle_len;
	int		i;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*(haystack + i) != '\0' && i <= ((int)len - needle_len))
	{
		if (*(haystack + i) == *needle)
			if (ft_strncmp((haystack + i), needle, needle_len) == 0)
				return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

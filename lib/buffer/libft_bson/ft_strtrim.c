/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:24:09 by bson              #+#    #+#             */
/*   Updated: 2022/01/13 16:14:24 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*get_start_point_or_null(const char *start, const char *set)
{
	while (ft_strchr(set, *start))
	{
		start++;
		if (*start == '\0')
			return (NULL);
	}
	return (start);
}

size_t	get_length_for_trim(const char *start, const char *set)
{
	size_t	idx;

	idx = (ft_strlen(start) - 1);
	while (ft_strchr(set, start[idx]))
	{
		idx--;
		if (idx == 0)
			return (1);
	}
	return (idx + 1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		len;
	char		*temp;
	const char	*start_ptr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start_ptr = get_start_point_or_null(s1, set);
	if (start_ptr == NULL)
		return (ft_strdup(""));
	len = get_length_for_trim(start_ptr, set);
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, start_ptr, len + 1);
	return (temp);
}

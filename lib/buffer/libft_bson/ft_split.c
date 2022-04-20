/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:36:48 by bson              #+#    #+#             */
/*   Updated: 2022/01/13 16:28:52 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_split(const char *str, const char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
		if (*str != '\0')
			str++;
	}
	return (count);
}

size_t	get_length_next_set(const char *s, const char c)
{
	size_t	length;

	length = 0;
	while (*s && *s != c)
	{
		length++;
		s++;
	}
	return (length);
}

char	**ft_split(char *str, char c)
{
	char		**split_table;
	size_t		index;

	if (str == NULL)
		return (NULL);
	split_table = malloc(sizeof(char *) * (count_split(str, c) + 1));
	if (!split_table)
		return (NULL);
	index = 0;
	while (*str)
	{
		if (*str != c)
		{
			split_table[index] = malloc(get_length_next_set(str, c) + 1);
			if (!split_table[index])
				return (NULL);
			ft_strlcpy(split_table[index++], str, \
			get_length_next_set(str, c) + 1);
			str += get_length_next_set(str, c);
		}
		if (*str)
			str++;
	}
	split_table[index] = NULL;
	return (split_table);
}

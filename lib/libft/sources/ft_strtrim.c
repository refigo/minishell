/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 11:43:53 by mgo               #+#    #+#             */
/*   Updated: 2021/05/19 17:58:54 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char const *set, char c)
{
	while (*set)
		if (*(set++) == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		len;

	if (!s1 || !set)
		return (NULL);
	while (*s1)
	{
		if (!(ft_isinset(set, *s1)))
			break ;
		s1++;
	}
	len = ft_strlen(s1);
	while (--len >= 0)
	{
		if (!(ft_isinset(set, s1[len])))
			break ;
	}
	trimmed = (char *)malloc(len + 2);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1, len + 2);
	return (trimmed);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:32:04 by mgo               #+#    #+#             */
/*   Updated: 2021/09/25 00:46:55 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*duped;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	duped = (char *)malloc(ft_strlen(s1) + 1);
	if (!duped)
		return (NULL);
	while (s1[i])
	{
		duped[i] = s1[i];
		i++;
	}
	duped[i] = '\0';
	return (duped);
}

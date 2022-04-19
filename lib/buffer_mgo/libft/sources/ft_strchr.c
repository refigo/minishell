/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:24:51 by mgo               #+#    #+#             */
/*   Updated: 2021/05/14 14:04:39 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr_c;

	chr_c = (char)c;
	while (*s != '\0')
	{
		if (*s == chr_c)
			return ((char *)s);
		s++;
	}
	if ((chr_c == '\0') && (*s == '\0'))
		return ((char *)s);
	return (NULL);
}

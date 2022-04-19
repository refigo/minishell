/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:34:28 by mgo               #+#    #+#             */
/*   Updated: 2021/05/13 20:14:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((uc_s1[i] == '\0') || (uc_s1[i] != uc_s2[i]))
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	return (0);
}

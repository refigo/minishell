/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgo_strcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:29:57 by mgo               #+#    #+#             */
/*   Updated: 2022/02/15 14:45:51 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	mgo_strcmp(const char *s1, const char *s2)
{
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;
	int				i;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	i = 0;
	while (uc_s1[i] || uc_s2[i])
	{
		if (uc_s1[i] != uc_s2[i])
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	return (0);
}

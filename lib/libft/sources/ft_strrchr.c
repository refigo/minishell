/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:09:15 by mgo               #+#    #+#             */
/*   Updated: 2021/05/14 14:10:29 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	chr_c;

	chr_c = (char)c;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (0 <= i)
	{
		if (s[i] == chr_c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

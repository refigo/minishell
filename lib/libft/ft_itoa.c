/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:53:00 by bson              #+#    #+#             */
/*   Updated: 2022/01/13 19:57:51 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_number_len(int nbr)
{
	int	count;

	count = 1;
	nbr /= 10;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int c)
{
	int		flag_minus;
	int		count;
	char	*result;

	flag_minus = 1;
	if (c >= 0)
		flag_minus = 0;
	count = ft_number_len(c);
	result = malloc(sizeof(char) * (count + flag_minus + 1));
	if (result == NULL)
		return (NULL);
	result[count + flag_minus] = '\0';
	while (count--)
	{
		result[count + flag_minus] = '0' + ft_abs(c % 10);
		c /= 10;
	}
	if (flag_minus)
		result[0] = '-';
	return (result);
}

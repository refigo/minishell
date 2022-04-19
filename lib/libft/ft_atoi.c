/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:58:46 by bson              #+#    #+#             */
/*   Updated: 2022/01/27 03:55:58 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || \
			*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result > 2147483647 && sign == 1)
			return (0);
		if (result > 2147483648 && sign == -1)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || \
			*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return ((result * sign));
}

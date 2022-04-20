/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:35:44 by mgo               #+#    #+#             */
/*   Updated: 2021/05/17 16:20:30 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_recursively(long long n, int fd, char *num_set)
{
	if (n > 9)
		put_recursively(n / 10, fd, num_set);
	write(fd, &(num_set[n % 10]), 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char		*num_set;
	long long	ll_n;

	num_set = "0123456789";
	ll_n = n;
	if (0 == n)
	{
		write(fd, "0", 1);
		return ;
	}
	if (ll_n < 0)
	{
		write(fd, "-", 1);
		ll_n *= -1;
	}
	put_recursively(ll_n, fd, num_set);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bson <bson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:27:33 by bson              #+#    #+#             */
/*   Updated: 2021/05/13 15:22:50 by bson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_nbr_recursive_only_positive(int n, int fd)
{
	char	*base;

	base = "0123456789";
	if (n < 0)
		return ;
	if (n >= 10)
		print_nbr_recursive_only_positive(n / 10, fd);
	write(fd, &base[n % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	print_nbr_recursive_only_positive(n, fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:55:29 by tsharma           #+#    #+#             */
/*   Updated: 2022/04/29 20:02:39 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_number(int n, int fd)
{
	char	c[10];
	int		counter;
	int		a;

	counter = 0;
	while (n > 0)
	{
		a = n % 10;
		c[counter] = '0' + a;
		counter++;
		n = n / 10;
	}
	counter = counter - 1;
	while (counter >= 0)
	{
		ft_putchar_fd(c[counter], fd);
		counter--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			n = n * -1;
			ft_putchar_fd('-', fd);
			ft_print_number(n, fd);
		}
	}
	else if (n == 0)
		ft_putchar_fd(48, fd);
	else
		ft_print_number(n, fd);
}

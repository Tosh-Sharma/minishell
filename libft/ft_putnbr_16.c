/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:32:51 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/11 18:34:31 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printnbr_16(int num, int fd)
{
	char	c[12];
	int		counter;

	counter = 0;
	while (num > 0)
	{
		c[counter] = "0123456789abcdef"[num % 16];
		counter++;
		num = num / 16;
	}
	counter = counter - 1;
	while (counter >= 0)
	{
		ft_putchar_fd(c[counter], fd);
		counter--;
	}
}

void	ft_putnbr_16(int num, int fd)
{
	if (num == 0)
		ft_putchar_fd('0', 1);
	else if (num < 0)
	{
		num = num * -1;
		ft_putchar_fd('-', fd);
	}
	ft_printnbr_16(num, fd);
}

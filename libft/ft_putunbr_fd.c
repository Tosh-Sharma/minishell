/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:09:35 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/19 16:35:47 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_unumber(unsigned int n, int fd)
{
	char	c[20];
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

void	ft_putunbr_fd(unsigned int n, int fd)
{
	if (n == 0)
		ft_putchar_fd(48, fd);
	else
		ft_print_unumber(n, fd);
}

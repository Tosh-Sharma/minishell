/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:54:51 by tvincile          #+#    #+#             */
/*   Updated: 2022/06/04 13:55:51 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_number_len(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == '0')
		i++;
	if (!str[i])
		return (1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ps_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	if (!str || !ft_number_len(str) || ft_number_len(str) > 10)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	if ((res > INT_MAX && sign == 1) || (res < INT_MIN && sign == -1))
		return (0);
	return (res * sign);
}

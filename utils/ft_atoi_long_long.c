/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:45:12 by tsharma           #+#    #+#             */
/*   Updated: 2022/07/18 18:52:50 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace_super(char i)
{
	if (i == ' ' || i == '\t' || i == '\n'
		|| i == '\v' || i == '\f' || i == '\r')
		return (1);
	return (0);
}

int	flip_if_negative_super(char str, int is_neg)
{
	if (str == 45)
	{
		if (is_neg)
			return (0);
		return (1);
	}
	return (is_neg);
}

long long	calculate_number_super(const char *str, int is_neg)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	// if (str[i] == 0)
	// 	exit(255);
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		num = (num * 10) + (str[i] - 48);
		if ((num > 922337203685477580 && str[i + 1] != '\0') || (num == 922337203685477580
				&& ((is_neg && str[i + 1] > 56)
					|| (!(is_neg) && str[i + 1] > 55))))
		{
			my_exit(255);
		}
		i++;

	}
	if ((str[i] < 48 || str[i] > 57) && str[i] != 0)
		my_exit(255);
	if (is_neg)
		return (num * -1);
	else
		return (num);
}

long long	ft_superatoi(const char *str)
{
	int		i;
	int		is_neg;

	i = 0;
	is_neg = 0;
	while (ft_isspace_super(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		is_neg = flip_if_negative_super(str[i], is_neg);
		i++;
	}
	return (calculate_number_super(&str[i], is_neg));
}

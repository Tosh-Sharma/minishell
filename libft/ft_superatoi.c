/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superatoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:12:43 by tsharma           #+#    #+#             */
/*   Updated: 2022/11/08 15:48:59 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include "libft.h"

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

int	calculate_number_super(const char *str, int is_neg, int *a)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (str[i] == 0)
		exit_program(a);
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		num = (num * 10) + (str[i] - 48);
		if ((num > 214748364 && str[i + 1] != '\0') || (num == 214748364
				&& ((is_neg && str[i + 1] > 56)
					|| (!(is_neg) && str[i + 1] > 55))))
			exit_program(a);
		i++;
	}
	if ((str[i] < 48 || str[i] > 57) && str[i] != 0)
		exit_program(a);
	if (is_neg)
		return (num * -1);
	else
		return (num);
}

int	ft_superatoi(const char *str, int *a)
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
	return (calculate_number_super(&str[i], is_neg, a));
}

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

int	ft_isspace_long_long(char i)
{
	if (i == ' ' || i == '\t' || i == '\n'
		|| i == '\v' || i == '\f' || i == '\r')
		return (1);
	return (0);
}

long long	flip_if_negative_long_long(char str, long long is_neg)
{
	if (str == 45)
	{
		if (is_neg)
			return (0);
		return (1);
	}
	return (is_neg);
}

long long   calculate_number_long_long(const char *str, long long is_neg)
{
    int         i;
	long long	num;

	i = 0;
	num = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (is_neg)
		return (num * -1);
	else
		return (num);
}

long long	ft_atoi_long_long(const char *str)
{
    long long   i;
	long long   is_neg;

	i = 0;
	is_neg = 0;
	while (ft_isspace_long_long(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		is_neg = flip_if_negative_long_long(str[i], is_neg);
		i++;
	}
	return (calculate_number_long_long(&str[i], is_neg));
}

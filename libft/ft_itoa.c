/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:18:09 by tsharma           #+#    #+#             */
/*   Updated: 2022/08/14 21:02:38 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*handle_num(int n, int is_neg, int i)
{
	char	s[11];
	char	*res;
	int		j;

	while (n > 0)
	{
		s[i] = '0' + (n % 10);
		i++;
		n = n / 10;
	}
	s[i] = '\0';
	res = (char *)malloc(sizeof(char) * (i + is_neg));
	if (!res)
		return (NULL);
	j = is_neg;
	i--;
	if (is_neg == 1)
		res[0] = '-';
	while (j - is_neg <= i)
	{
		res[j] = s[i - j + is_neg];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	else
	{
		if (n < 0)
			return (handle_num(n * -1, 1, i));
		return (handle_num(n, 0, i));
	}
}

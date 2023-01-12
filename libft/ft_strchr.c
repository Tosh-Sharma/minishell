/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:47:37 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/03 20:26:37 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			res = (char *)&s[i];
			return (res);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		res = (char *)&s[i];
		return (res);
	}
	return (NULL);
}

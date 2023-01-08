/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:58:27 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/04 14:12:42 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void				*res;
	unsigned const char	*temp;
	size_t				i;
	unsigned char		cmp;

	temp = s;
	cmp = c;
	i = 0;
	while (i < n)
	{
		if (temp[i] == cmp)
		{
			res = (void *)&s[i];
			return (res);
		}
		i++;
	}
	return (NULL);
}

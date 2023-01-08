/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:45:37 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/09 15:10:43 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)b)[i] == (unsigned char)c)
			return ((void *)(b + i));
		i++;
	}
	return (0);
}
/*
{
	char	*s;

	s = (char *) b;
	while (n > 0)
	{
		if (*s == (char) c)
			return (s);
		s++;
		n--;
	}
	return (0);
}
*/
// renvoit le premier encounter avec &c dans &b

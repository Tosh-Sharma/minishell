/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:05:23 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/05 17:31:34 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	lens;
	size_t	i;

	if (!s)
		return (0);
	lens = ft_strlen(s);
	i = 0;
	if (start < lens)
		i = lens - start;
	if (i > len)
		i = len;
	s1 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s1)
		return (0);
	ft_strlcpy(s1, s + start, i + 1);
	return (s1);
}
// decoupe &s et alloue de la memoire equivalente 
// a l'espace entre &start et &len et en fait la copie dans &s1
/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s1;

	s1 = (char*)malloc(sizeof(*s) * (len));
	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			s1[j] = s[i]; 
			j++;
		}
		i++;
	}
	s1[j] = '\0';
	return (s1);
}*/

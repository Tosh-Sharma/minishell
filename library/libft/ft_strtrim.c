/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:48:47 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/05 17:31:13 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_valid(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	lens1;
	char	*str;

	start = 0;
	lens1 = ft_strlen(s1);
	while (s1[start] != '\0' && ft_char_valid(s1[start], set) == 1)
		start++;
	while (lens1 > start && ft_char_valid(s1[lens1 - 1], set) == 1)
		lens1--;
	str = malloc(sizeof(*s1) * (lens1 - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < lens1)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
// Decoupe &s1 entre le premier 
// et dernier groupe de caracteres contenus dans &set 
// et alloue de la memoire

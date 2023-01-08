/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:57:22 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/05 16:50:21 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*world;

	world = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!world)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		world[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		world[j] = s2[i];
		j++;
		i++;
	}
	world[j] = '\0';
	return (world);
}
// Concatene &s1 et &s2 dans &world et alloue de la memoire 

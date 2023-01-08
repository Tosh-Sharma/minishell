/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:10:53 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/05 17:30:30 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (needle[i] != 0)
		i++;
	if (i == 0)
		return ((char *)(haystack));
	i = 0;
	while (haystack[i] != 0 && i < len)
	{
		j = 0;
		while (haystack[i + j] != 0 && needle[j] != 0
			&& i + j < len && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
// regarde si &needle est present dans &haystack pour &len caracteres, 
// si oui on renvoit haystack a partir de la premiere occurence

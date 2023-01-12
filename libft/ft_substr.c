/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:11:17 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/03 20:02:13 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	str_len;
	size_t	size;
	char	*res;

	i = 0;
	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return ((char *)ft_calloc(1, 1));
	if (len > (str_len - start))
		size = str_len - start + 1;
	else
		size = len + 1;
	res = malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

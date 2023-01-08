/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:43:09 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/03 19:36:55 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	front_trimmer(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	flag;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		flag = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
				flag = 1;
			j++;
		}
		if (flag != 1)
			break ;
		i++;
	}
	return (i);
}

size_t	back_trim(const char *res, char const *set)
{
	size_t	length;
	size_t	i;
	size_t	j;
	size_t	flag;

	i = 0;
	length = ft_strlen(res);
	while (i < length)
	{
		flag = 0;
		j = 0;
		while (set[j] != '\0')
		{
			if (res[length - 1 - i] == set[j])
				flag = 1;
			j++;
		}
		if (flag == 0)
			break ;
		i++;
	}
	return (length - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		length;
	size_t		start;
	char		*result;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup((char *)s1));
	start = front_trimmer(s1, set);
	length = back_trim(&s1[start], set);
	result = ft_substr(s1, start, length);
	return (result);
}

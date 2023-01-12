/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:12:27 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/03 19:45:55 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(const char *s, char c)
{
	size_t	count;
	size_t	flag;
	size_t	i;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static void	length_count(size_t count, const char *s, char c, size_t *sc)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0' && k < count)
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		sc[k] = i - j;
		k++;
	}
}

static void	copy_word(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	**split_it(const char *s, char c, size_t count, size_t *size_count)
{
	size_t	i;
	size_t	k;
	char	**res;

	res = (char **)malloc((sizeof(char **)) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (k < count)
	{
		while (s[i] == c)
			i++;
		res[k] = (char *)malloc(sizeof(char) * size_count[k] + 1);
		if (!res[k])
			return (NULL);
		copy_word(res[k], (char *)&s[i], size_count[k]);
		i = i + size_count[k] + 1;
		k++;
	}
	free(size_count);
	res[count] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	size_t	*size_count;

	if (s == NULL)
		return (NULL);
	count = counter(s, c);
	size_count = (size_t *)malloc(sizeof(size_t) * count);
	if (!size_count)
		return (NULL);
	length_count(count, s, c, size_count);
	return (split_it(s, c, count, size_count));
}

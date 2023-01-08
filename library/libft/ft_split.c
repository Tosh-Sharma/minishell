/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:32:41 by tvincile          #+#    #+#             */
/*   Updated: 2022/05/25 12:19:53 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_words(char const *s, char c)
{
	int	nb;
	int	is_c;

	if (!s)
		return (0);
	nb = 0;
	is_c = 0;
	while (*s != '\0')
	{
		if (*s != c && is_c == 0)
		{
			is_c = 1;
			nb++;
		}
		else if (*s == c)
			is_c = 0;
		s++;
	}
	return (nb);
}

static char	*ft_print_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		start_word;
	char	**split;

	split = malloc((ft_nb_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	start_word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_word < 0)
			start_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_word >= 0)
		{
			split[j++] = ft_print_word(s, start_word, i);
			start_word = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
// ft_nb_words compte le nombre de caracteres qui seront dans split, 
// ft_print_word les converti en chaines de caracteres 
// ces chaines sont delimites dans le ft_split 
// qui le fait en fonction de &c (exclu) 

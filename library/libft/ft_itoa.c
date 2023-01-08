/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvincile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:30:27 by tvincile          #+#    #+#             */
/*   Updated: 2022/04/05 17:25:11 by tvincile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_numb(int n)
{
	int	nb;

	nb = 0;
	if (n == 0)
		nb++;
	while (n > 9)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

static void	ft_recputnbr(int nb, int *i, char *n_char)
{
	if (nb == -2147483648)
	{
		n_char[0] = '-';
		(*i)++;
		ft_recputnbr(21474, i, n_char);
		ft_recputnbr(83648, i, n_char);
	}
	else if (nb < 0)
	{
		n_char[0] = '-';
		(*i)++;
		ft_recputnbr(-nb, i, n_char);
	}
	else if (nb >= 10)
	{
		ft_recputnbr(nb / 10, i, n_char);
		ft_recputnbr(nb % 10, i, n_char);
	}
	else
	{
		n_char[(*i)++] = nb + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*n_char;
	int		i;

	i = 0;
	if (n < 0)
		n_char = malloc(sizeof(char) * (ft_nb_numb(n) + 2));
	else
		n_char = malloc(sizeof(char) * (ft_nb_numb(n) + 1));
	if (!n_char)
		return (NULL);
	ft_recputnbr(n, &i, n_char);
	n_char[i++] = '\0';
	return (n_char);
}
// Compte le nombre de chiffres dans &n, 
// le transfo en chaine de char et alloue de la memoire

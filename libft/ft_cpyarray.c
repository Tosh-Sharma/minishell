/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:27:52 by tsharma           #+#    #+#             */
/*   Updated: 2022/08/14 16:03:23 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_cpyarray(int *dst, int *src, int n)
{
	int	i;

	i = 0;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

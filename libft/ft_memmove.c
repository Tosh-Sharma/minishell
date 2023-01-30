/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:13:04 by tsharma           #+#    #+#             */
/*   Updated: 2022/04/25 16:29:17 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*src_cpy;
	unsigned char		*dst_cpy;
	size_t				i;

	i = len;
	src_cpy = src;
	dst_cpy = dst;
	if (dst > src)
	{
		while (i > 0)
		{
			dst_cpy[i - 1] = src_cpy[i - 1];
			i--;
		}
		return (dst_cpy);
	}
	else
		return (ft_memcpy(dst, src, len));
}

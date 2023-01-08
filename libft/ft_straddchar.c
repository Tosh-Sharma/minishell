/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:52:32 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/19 16:35:23 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchar(char const *src, char c)
{
	size_t	len;
	char	*res;

	len = ft_strlen(src);
	res = (char *)malloc(sizeof(char) * (len + 2));
	ft_strlcpy(res, src, len + 1);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}

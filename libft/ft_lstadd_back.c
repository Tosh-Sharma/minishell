/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:31:09 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/02 20:46:45 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (lst != NULL)
	{
		if (lst[0] == NULL)
			lst[0] = new;
		else
		{
			p = lst[0];
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

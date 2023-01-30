/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:54:56 by tsharma           #+#    #+#             */
/*   Updated: 2022/05/03 11:59:39 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*current;
	t_list	*prev;
	t_list	*element;

	current = lst;
	res = NULL;
	while (current)
	{
		element = ft_lstnew(f(current->content));
		if (!element)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, element);
		prev = current;
		current = current->next;
	}
	return (res);
}

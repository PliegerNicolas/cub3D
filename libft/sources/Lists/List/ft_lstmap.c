/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:17:51 by emis              #+#    #+#             */
/*   Updated: 2022/11/11 12:21:18 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*result;
	t_list	*newnode;

	current = lst;
	result = NULL;
	while (current)
	{
		newnode = ft_lstnew(f(current -> content));
		if (!newnode)
		{
			ft_lstclear(&result, del);
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&result, newnode);
		current = current -> next;
	}
	return (result);
}

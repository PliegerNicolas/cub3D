/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:17:51 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 14:36:33 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_clist	*ft_clstmap(t_clist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_clist	*current;
	t_clist	*result;
	t_clist	*newnode;
	t_clist	*start;

	current = lst;
	start = current;
	result = NULL;
	while (!result || current != start)
	{
		newnode = ft_clstnew(f(current -> cont));
		if (!newnode)
		{
			ft_clstclear(&result, del);
			ft_clstclear(&lst, del);
			return (NULL);
		}
		ft_clstadd_back(&result, newnode);
		current = current -> next;
	}
	return (result);
}

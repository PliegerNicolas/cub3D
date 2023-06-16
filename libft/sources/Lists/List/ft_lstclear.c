/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:03:22 by emis              #+#    #+#             */
/*   Updated: 2022/11/13 10:41:41 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*nextup;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		nextup = current -> next;
		ft_lstdelone(current, del);
		current = nextup;
	}
	*lst = NULL;
}

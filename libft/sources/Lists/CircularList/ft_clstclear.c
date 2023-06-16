/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:03:22 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 14:47:12 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clstclear(t_clist **lst, void (*del)(void *))
{
	t_clist	*current;
	t_clist	*nextup;
	t_clist	*start;

	if (!lst || !del)
		return ;
	current = *lst;
	start = current;
	nextup = NULL;
	while (nextup != start)
	{
		nextup = current -> next;
		ft_clstdelone(current, del);
		current = nextup;
	}
	*lst = NULL;
}

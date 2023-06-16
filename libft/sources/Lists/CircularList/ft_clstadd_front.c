/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:36:17 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 15:49:25 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clstadd_front(t_clist **lst, t_clist *new)
{
	t_clist	*tmp;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = (*lst)->prev;
		new -> next = *lst;
		(*lst)->prev = new;
		*lst = new;
		(*lst)->prev = tmp;
		tmp -> next = *lst;
	}
}

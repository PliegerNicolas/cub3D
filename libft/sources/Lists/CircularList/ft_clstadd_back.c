/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:46:15 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 15:50:15 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clstadd_back(t_clist **lst, t_clist *new)
{
	if (!(*lst))
		*lst = new;
	else
	{
		new -> next = *lst;
		new -> prev = (*lst)->prev;
		((*lst)->prev)->next = new;
		(*lst)->prev = new;
		if ((*lst)->next == *lst)
			(*lst)->next = new;
	}
}

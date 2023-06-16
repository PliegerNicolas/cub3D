/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:15:08 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 15:33:54 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clstiter(t_clist *lst, void (*f)(void *))
{
	t_clist	*current;
	t_clist	*start;

	current = lst;
	start = current;
	while (current -> next != start)
	{
		f(current -> cont);
		current = current -> next;
	}
	f(current -> cont);
}

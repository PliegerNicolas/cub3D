/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:38:26 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 15:21:19 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_clstsize(t_clist *lst)
{
	int		n;
	t_clist	*current;
	t_clist	*start;

	n = 0;
	current = lst;
	start = current;
	if (current && current -> next == current)
		return (1);
	while (current && (!n || current != start))
	{
		n++;
		current = current -> next;
	}
	return (n);
}

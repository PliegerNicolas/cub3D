/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:38:26 by emis              #+#    #+#             */
/*   Updated: 2022/11/10 11:58:59 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*current;

	n = 0;
	current = lst;
	while (current)
	{
		n++;
		current = current -> next;
	}
	return (n);
}

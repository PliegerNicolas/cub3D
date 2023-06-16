/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:43:09 by emis              #+#    #+#             */
/*   Updated: 2022/11/11 11:51:30 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current && current -> next)
	{
		current = current -> next;
	}
	return (current);
}

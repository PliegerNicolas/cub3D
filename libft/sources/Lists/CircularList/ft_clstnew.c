/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:27:39 by emis              #+#    #+#             */
/*   Updated: 2022/12/08 15:47:58 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_clist	*ft_clstnew(void *content)
{
	t_clist	*new;

	new = malloc(sizeof(t_clist));
	if (!new)
		return (NULL);
	new -> cont = content;
	new -> next = new;
	new -> prev = new;
	return (new);
}

/*
#include <stdio.h>

void	printy(void *stuff)
{
	printf("%s\n", (char *)stuff);
}

void	*stuffy(void *stuff)
{
	(*((char *) stuff))++;
	return (stuff);
}

void	dely(void *stuff)
{
	free((char *)stuff);
}

int main() //TESTING CLISTS
{
	t_clist	*first, *second, *third, *fourth, *fifth, *current;
	first = ft_clstnew(ft_strdup("1"));
	second = ft_clstnew(ft_strdup("2"));
	// ft_clstadd_back(&first, second);
	ft_clstadd_front(&first, second);
	third = ft_clstnew(ft_strdup("3"));
	// ft_clstadd_back(&first, third);
	ft_clstadd_front(&first, third);
	fourth = ft_clstnew(ft_strdup("4"));
	// ft_clstadd_back(&first, fourth);
	ft_clstadd_front(&first, fourth);
	fifth = ft_clstnew(ft_strdup("5"));
	ft_clstadd_front(&first, fifth);
	// current = ft_clstlast(first); //first
	// for (int i = 0; i < 15; i++)
	// {
	// 	printf("iter%d: %s\n", i, ((char *)current->cont));
	// 	current = current -> next;
	// }
	printf("size %d\n", ft_clstsize(first));
	printf("last %s\n", (char *)ft_clstlast(fifth)->cont);
	ft_clstiter(first, printy);
	// current = ft_clstmap(first, stuffy, printy);
	// ft_clstiter(current, printy);
	ft_clstclear(&first, dely);
	// printf("deleted? %s\n", (char *)first->cont);
	printf("deleted? %p\n", first);
	// current = first;
	// for (int i = 0; i < 15; i++)
	// {
	// 	printf("iter%d: %s\n", i, ((char *)current->cont));
	// 	current = current -> prev;
	// }
}
*/
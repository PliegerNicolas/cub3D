/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:55:34 by emis              #+#    #+#             */
/*   Updated: 2022/11/11 11:30:52 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = -1;
	if (!dest && !src)
		return (0);
	while (++i < (int)n)
		*(((char *)dest) + i) = *(((char *)src) + i);
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int main () {
	// char *dest = NULL; //malloc(56);
	// char *dest1 = NULL;
	//char stuff[50] = "i love spaghetti my guy";

	// ft_memcpy(dest1, dest, 3);
	printf("dest1 = %s\n", (char *)memcpy(((void*)0), ((void*)0), 3));
	return(0);
}
*/
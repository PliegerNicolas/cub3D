/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:10:36 by emis              #+#    #+#             */
/*   Updated: 2022/11/10 15:32:35 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		while (n--)
			*(((char *)dest) + n) = *(((char *)src) + n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/*
#include <stdio.h>

int main () {
	char *dest = malloc(56);
	char stuff[50] = "i love spaghetti my guy";


	if (!dest || !src)
		return (NULL);

	ft_memmove(dest, stuff, ft_strlen(stuff)+1);
	printf("dest = %s\n", dest);
	return(0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:30:13 by emis              #+#    #+#             */
/*   Updated: 2022/11/10 15:33:51 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && *(unsigned char *)s1 == *(unsigned char *)s2)
	{
		s1++;
		s2++;
		i++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*
if (*(unsigned char *)s1 == 0)
			return (0);
*/
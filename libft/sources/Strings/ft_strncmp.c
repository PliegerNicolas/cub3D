/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:14:14 by emis              #+#    #+#             */
/*   Updated: 2022/11/08 13:17:23 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && *s1 == *s2)
	{
		if (*s1 == 0)
			return (0);
		s1++;
		s2++;
		i++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

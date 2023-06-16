/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:55 by emis              #+#    #+#             */
/*   Updated: 2022/11/13 10:30:05 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (!s)
		return (NULL);
	sub = malloc(sizeof(*s) * (len + 1));
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < (int)len && start < ft_strlen((char *)s))
		sub[i] = s[i + start];
	sub[i] = 0;
	return (sub);
}

/*
#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", ft_substr("bob est tres beau mais bob", 3, 23));
}
*/
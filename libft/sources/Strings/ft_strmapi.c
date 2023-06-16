/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:19:53 by emis              #+#    #+#             */
/*   Updated: 2022/11/13 10:32:53 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mapi;

	if (!s || !f)
		return (NULL);
	mapi = malloc(ft_strlen((char *)s) + 1);
	if (!mapi)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = 0;
	return (mapi);
}

/*
#include <stdio.h>
char	rot1(unsigned int r, char c)
{
	return (c + r);
}

int main()
{
	printf("Bonsoir, %s\n", ft_strmapi("I like chicken", rot1));
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:35:41 by emis              #+#    #+#             */
/*   Updated: 2022/11/14 10:52:28 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == 0 || big == little)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			j++;
			if (!little[j])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

/*
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	litlen;
	size_t	biglen;
	size_t	i;

	if (little)
		litlen = ft_strlen((char *)little);
	i = 0;
	if (little[0] == 0 || big == little)
		return ((char *)big);
	if (len)
		biglen = ft_strlen((char *)big);
	while (i + litlen < len + 1 && i + litlen < biglen + 1)
	{
		if (!ft_strncmp((char *)(big + i), (char *)little, litlen))
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", 
	ft_strnstr("see FF your FF return FF now PK\0 hello", "hello", 1000));
}
*/
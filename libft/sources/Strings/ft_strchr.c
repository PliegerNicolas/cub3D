/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:03:28 by emis              #+#    #+#             */
/*   Updated: 2022/11/10 16:23:25 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen((char *)s))
		if (s[i] == c)
			break ;
	if (c == 0 || s[i] != 0)
		return ((char *)(&s[i]));
	else
		return (NULL);
}

/*
#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", ft_strchr("bob est tres beau mais bob", 'e'));
}
*/
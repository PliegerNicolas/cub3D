/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:30:46 by emis              #+#    #+#             */
/*   Updated: 2022/11/13 10:30:50 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = 0;
	return (join);
}

/*
#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", ft_strjoin("je suis sexy", "\n"));
}
*/
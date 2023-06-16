/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:07:15 by emis              #+#    #+#             */
/*   Updated: 2022/11/10 10:25:49 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s) + 1;
	while (--i != -1)
		if (s[i] == c)
			break ;
	if (c == 0 || i != -1)
		return ((char *)&s[i]);
	else
		return (NULL);
}

/*
#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", ft_strrchr("kob est tres beau mais bob", '0') 
	== NULL ? "(null)" : ft_strrchr("kob est tres beau mais bob", '0') );
}
*/
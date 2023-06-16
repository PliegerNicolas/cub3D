/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:47:05 by emis              #+#    #+#             */
/*   Updated: 2022/11/13 10:31:30 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char const *set, char c)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	start;
	size_t	end;

	i = -1;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen((char *)s1);
	while (s1[++i])
	{
		if (!inset(set, s1[i]) && inset(set, s1[start]))
			start = i;
		else if (i > 0 && !inset(set, s1[i - 1]) && inset(set, s1[i])
			&& inset(set, s1[ft_strlen((char *)s1) - 1]))
			end = i;
	}
	if (end == ft_strlen((char *)s1) && inset(set, s1[end - 1]))
		end = start;
	return (ft_substr(s1, start, end - start));
}

/*
#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", ft_strtrim("biuGUGBFJEBfiuhwGIUHkjbfuHF",
	 "biuGUGBFJEBfiuhwGIUHjbfuHF"));
}
*/
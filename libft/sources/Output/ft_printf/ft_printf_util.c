/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:30:54 by emis              #+#    #+#             */
/*   Updated: 2022/11/19 14:09:05 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	insetend(char const *set, char c, char end)
{
	while (*set != end)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*tnx(char *fmt, char c)
{
	while (*fmt && *fmt != c)
		fmt++;
	return (fmt);
}

char	*tnxnb(char *fmt)
{
	while (*fmt && !insetend("123456789", *fmt, 0))
		fmt++;
	return (fmt);
}

char	*tnxhx(char *fmt)
{
	while (*fmt && !insetend("123456789abcdefABCDEF", *fmt, 0))
		fmt++;
	return (fmt);
}

char	*ft_strncpyfree(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	free(src);
	return (dest);
}

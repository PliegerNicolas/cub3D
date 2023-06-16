/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:42:38 by emis              #+#    #+#             */
/*   Updated: 2022/11/19 10:55:49 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*strfrmchr(char c)
{
	char	*stch;

	stch = malloc(2);
	if (!stch)
		return (NULL);
	stch[0] = c;
	stch[1] = 0;
	return (stch);
}

char	*strfrmstr(char *str, int fr)
{
	char	*dup;

	if (str)
		dup = ft_strdup(str);
	else
		dup = NULL;
	if (fr && str)
		free(str);
	return (dup);
}

static char	*mkhexnbr(unsigned long long n, char *base)
{
	unsigned long long	size;
	unsigned long long	copy;
	char				*nbr;

	size = 0;
	copy = n;
	while (copy && ++size)
		copy /= 16;
	nbr = malloc(sizeof(char) * (size + 2));
	if (!nbr)
		return (NULL);
	if (size == 0)
	{
		nbr[0] = '0';
		nbr[1] = 0;
		return (nbr);
	}
	nbr[size] = 0;
	while (size--)
	{
		nbr[size] = base[n % 16];
		n /= 16;
	}
	return (nbr);
}

char	*strfrmptr(void *ptr)
{
	char	*dup;
	char	*hex;
	int		i;

	if (!ptr)
		return (ft_strdup("(nil)"));
	hex = mkhexnbr((unsigned long long)ptr, "0123456789abcdef");
	dup = malloc(ft_strlen(hex) + 3);
	if (!dup)
		return (NULL);
	i = -1;
	while (hex[++i])
		dup[i + 2] = hex[i];
	dup[i + 2] = 0;
	dup[0] = '0';
	dup[1] = 'x';
	free(hex);
	return (dup);
}

char	*strfrmhex(unsigned int hex, int big)
{
	if (big)
		return (mkhexnbr((unsigned long long)hex, "0123456789ABCDEF"));
	else
		return (mkhexnbr((unsigned long long)hex, "0123456789abcdef"));
}

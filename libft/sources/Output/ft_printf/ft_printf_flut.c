/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flut.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:08:20 by emis              #+#    #+#             */
/*   Updated: 2022/11/19 14:09:21 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	addprefix(char **res, char prefix)
{
	char	*cpy;
	char	*pfxptr;

	cpy = *res;
	pfxptr = cpy;
	if (insetend("xX", prefix, 0))
	{
		if (pfxptr[0] == ' ')
			pfxptr = tnxhx(cpy) - 2;
		pfxptr[0] = '0';
		if (pfxptr[1])
			pfxptr[1] = prefix;
	}
	else if (!insetend(cpy, '-', 0) && prefix != '+')
		pfxptr[0] = ' ';
	else if (!insetend(cpy, '-', 0) && pfxptr[0] == '0')
		pfxptr[0] = '+';
	else if (!insetend(cpy, '-', 0) && pfxptr[0] == ' ')
		*(tnxnb(pfxptr) - 1 - !ft_atoi(cpy)) = '+';
	else if (insetend(cpy, '-', 0) && pfxptr[0] == '0')
	{
		pfxptr[0] = '-';
		*(tnxnb(pfxptr) - 1) = '0';
	}
	*res = cpy;
}

char	*mkfield(int size, int zeropad)
{
	char	*dup;
	int		i;

	dup = malloc(size + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < size)
		dup[i] = ' ' + zeropad * 16;
	dup[i] = 0;
	return (dup);
}

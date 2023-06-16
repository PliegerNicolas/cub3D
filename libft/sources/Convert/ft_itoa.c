/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:52:46 by emis              #+#    #+#             */
/*   Updated: 2022/12/06 16:08:47 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*mknbr(unsigned int n)
{
	unsigned int	size;
	unsigned int	copy;
	char			*nbr;

	size = 0;
	copy = n;
	while (copy && ++size)
		copy /= 10;
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
		nbr[size] = (n % 10) + '0';
		n /= 10;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nb;
	int		neg;

	neg = 1;
	if (n < 0)
		n *= -1;
	else
		neg = 0;
	nb = mknbr((unsigned int)n);
	if (!nb)
		return (NULL);
	if (neg)
	{
		neg = ft_strlen(nb) + 1;
		nb[neg] = 0;
		while (--neg)
		{
			nb[neg] = nb[neg - 1];
		}
		nb[0] = '-';
	}
	return (nb);
}

/*
#include <stdio.h>

int main()
{
	printf("Bonsoir, %s\n", ft_itoa(-69420));
}
*/
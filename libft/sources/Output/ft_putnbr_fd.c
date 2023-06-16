/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:19:59 by emis              #+#    #+#             */
/*   Updated: 2022/11/11 11:22:51 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else if (n < 0 && n != -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * (-1), fd);
	}
	else
	{
		ft_putnbr_fd((n / 10), fd);
		if (n != -2147483648)
			ft_putchar_fd((n % 10) + '0', fd);
		else
			ft_putchar_fd('8', fd);
	}
}

/*
#include <stdio.h>

if (n == -2147483648)
		write(1, "-2147483648", 11);
	else 

int main()
{
	ft_putnbr_fd(-2, 1);
}
*/
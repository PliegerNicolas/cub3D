/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:04:52 by emis              #+#    #+#             */
/*   Updated: 2023/06/13 15:42:58 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbaj.h"

int	eerror(const char *__s)
{
	static int	e;

	if (!__s)
		return (e);
	if (!errno)
		return (0);
	if (!__s[0])
		perror(" ");
	else if (ft_strlen((char *)__s) > 15 && errno == 1)
		write(STDERR_FILENO, __s, ft_strlen((char *)__s));
	else
		perror(__s);
	return (++e);
}

void	try(int fail, char *name)
{
	if (!fail)
		return ;
	write(2, "Critical error\n", 15);
	eerror(name);
	garbaj(NULL, NULL, 0);
	exit(1);
}

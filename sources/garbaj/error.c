/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:04:52 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 23:12:18 by nicolas          ###   ########.fr       */
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
		ft_putendl_fd((char *)__s, STDERR_FILENO);
	else
		perror(__s);
	return (++e);
}

void	try(int fail, char *name)
{
	if (!fail)
		return ;
	ft_putendl_fd("Critical error", STDERR_FILENO);
	eerror(name);
	garbaj(NULL, NULL, 0);
	exit(1);
}

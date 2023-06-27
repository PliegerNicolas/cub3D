/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_incharset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:57:34 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/27 13:58:00 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	is_incharset(unsigned char c, char *charset)
{
	size_t	i;

	if (!charset)
		return (1);
	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

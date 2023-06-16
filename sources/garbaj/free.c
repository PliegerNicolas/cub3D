/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:40:59 by emis              #+#    #+#             */
/*   Updated: 2023/06/13 15:41:45 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbaj.h"

int	freewrap(void *obj)
{
	return (free(obj), 0);
}

int	free_ch_ar(char **ar)
{
	int	i;

	i = -1;
	if (!ar)
		return (1);
	while (ar[++i])
		free(ar[i]);
	free(ar);
	return (0);
}

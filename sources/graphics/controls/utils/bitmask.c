/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:14:33 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/16 15:47:18 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	is_mask_set(int *mask, t_rndr option)
{
	return ((*mask & option) != 0);
}

void	toggle_mask(int *mask, t_rndr option, t_rndr_toggle status)
{
	if (status == TOGGLE)
		*mask ^= option;
	else if (status == ON)
		*mask |= option;
	else if (status == OFF)
		*mask &= ~option;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:46:37 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/16 16:12:50 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	select_map_type(int *mask)
{
	if (!is_mask_set(mask, MINIMAP))
		toggle_mask(mask, MINIMAP, ON);
	else if (!is_mask_set(mask, MINIMAP_CIRCULAR))
		toggle_mask(mask, MINIMAP_CIRCULAR, ON);
	else if (!is_mask_set(mask, MINIMAP_FOCUS))
		toggle_mask(mask, MINIMAP_FOCUS, ON);
	else
	{
		toggle_mask(mask, MINIMAP, OFF);
		toggle_mask(mask, MINIMAP_CIRCULAR, OFF);
		toggle_mask(mask, MINIMAP_FOCUS, OFF);
	}
}

static void	turn_all_on(int *mask)
{
	toggle_mask(mask, TEXTUWALLS, ON);
	toggle_mask(mask, FLOORCEIL, ON);
	toggle_mask(mask, SPRITES, ON);
}

void	change_render_type(int *mask)
{
	static int	render_types;

	if (render_types == 0)
		toggle_mask(mask, SPRITES, OFF);
	else if (render_types == 1)
	{
		toggle_mask(mask, SPRITES, ON);
		toggle_mask(mask, FLOORCEIL, OFF);
	}
	else if (render_types == 2)
		toggle_mask(mask, SPRITES, OFF);
	else if (render_types == 3)
	{
		toggle_mask(mask, SPRITES, ON);
		toggle_mask(mask, TEXTUWALLS, OFF);
	}
	else if (render_types == 4)
		toggle_mask(mask, SPRITES, OFF);
	else if (render_types == 5)
		turn_all_on(mask);
	if (render_types >= 5)
		render_types = 0;
	else
		render_types++;
}

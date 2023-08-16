/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:14:33 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/16 13:09:53 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	is_mask_set(t_play *player, t_rndr option)
{
	return ((player->rndr & option) != 0);
}

void	change_render_type(t_play *player)
{
	static int	render_types;

	if (render_types == 0)
		player->rndr = TEXTUWALLS | FLOORCEIL | SPRITES; // 00000111 = 7
	else if (render_types == 1)
		player->rndr = TEXTUWALLS | FLOORCEIL; // 00000011 = 3
	else if (render_types == 2)
		player->rndr = TEXTUWALLS; // 00000001 = 1
	else if (render_types == 3)
		player->rndr = TEXTUWALLS | SPRITES; // 00000101 = 5
	else if (render_types == 4)
		player->rndr = FLOORCEIL; // 00000010 = 2
	else if (render_types == 5)
		player->rndr = EMPTY; // 00000000 = 0
	if (render_types >= 5)
		render_types = 0;
	else
		render_types++;
}

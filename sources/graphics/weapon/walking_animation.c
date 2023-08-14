/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:54:55 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/13 11:57:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

int	calculate_next_walk_frame(t_gui *gui, int frame)
{
	if (gui->cam.speed.x || gui->cam.speed.y)
		return ((frame + 1) % WALK_FREQUENCY);
	else if (frame != 0 && frame != (WALK_FREQUENCY * 0.5))
		return ((frame + 1) % WALK_FREQUENCY);
	return (0);
}

void	set_weapon_position(t_gui *gui, int *x, int *y, int frame)
{
	int		x_offset;
	int		y_offset;
	float	walk_angle;

	x_offset = gui->textures.weapon->width * 0.2;
	y_offset = gui->textures.weapon->height * 0.2 + gui->cam.pitch * SCRHEIGHT;
	if (gui->cam.speed.x || gui->cam.speed.y || frame)
	{
		walk_angle = (frame / (float)WALK_FREQUENCY
				* gui->cam.sprint_multiplicator) * 2 * M_PI;
		x_offset += (int)(sin(walk_angle) * WALK_AMPLITUDE);
		y_offset -= (int)(fabs(cos(walk_angle)) * WALK_AMPLITUDE / 2);
	}
	*x = SCRWIDTH - gui->textures.weapon->width + x_offset;
	*y = SCRHEIGHT - gui->textures.weapon->height + y_offset;
}

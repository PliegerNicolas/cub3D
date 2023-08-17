/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:54:55 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/17 18:00:37 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

int	calculate_next_walk_frame(t_gui *gui)
{
	static int		walk_frame;

	if (gui->cam.speed.x || gui->cam.speed.y)
		return ((walk_frame + 1) % WALK_FREQUENCY);
	else if (walk_frame != 0 && walk_frame != (WALK_FREQUENCY * 0.5))
		return ((walk_frame + 1) % WALK_FREQUENCY);
	return (0);
}

void	set_weapon_position(t_gui *gui, int *x, int *y, int frame)
{
	int		x_offset;
	int		y_offset;
	float	walk_angle;

	t_img	*img;
	img = gui->textures.spframes[SIZE + NB_OBJTYPE + NB_MOBTYPE][0];

	x_offset = img->width * 0.2;
	y_offset = img->height * 0.2 + gui->cam.pitch * SCRHEIGHT;
	if (gui->cam.speed.x || gui->cam.speed.y || frame)
	{
		walk_angle = (frame / (float)WALK_FREQUENCY
				* gui->cam.sprint_multiplicator) * 2 * M_PI;
		x_offset += (int)(sin(walk_angle) * WALK_AMPLITUDE);
		y_offset -= (int)(fabs(cos(walk_angle)) * WALK_AMPLITUDE / 2);
	}
	*x = SCRWIDTH - img->width + x_offset;
	*y = SCRHEIGHT - img->height + y_offset;
}

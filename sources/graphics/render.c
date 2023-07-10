/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 15:54:22 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

int	render(t_gui *gui)
{
	double	z_buffer[SCRWIDTH];

	if (gui->rendered && ((!gui->keys && !gui->cam.speed.x && !gui->cam.speed.y)
			&& gui->cam.rndr < SPRITES))
		return (0);
	key_render(gui);
	erase(gui->buffer);
	if (gui->cam.rndr == FLOORCEIL)
		floor_cast(gui);
	wall_cast(gui, z_buffer);
	if (gui->cam.rndr >= SPRITES)
	{
		sprite_cast(gui, z_buffer);
		weapon(gui);
	}
	minimap(gui);
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	gui->rendered = 1;
	return (0);
}

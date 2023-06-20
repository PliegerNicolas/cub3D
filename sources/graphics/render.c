/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 19:24:48 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

static void	key_render(t_gui *gui)
{
	if (!gui->keys)
		return;
	if (gui->keys & (1 << KP_sprint))
		gui->cam.speed = 2;
	else
		gui->cam.speed = 1;
	if (gui->keys & (1 << KP_rot_left))
		rotate(&gui->cam, 1);
	else if (gui->keys & (1 << KP_rot_right))
		rotate(&gui->cam, -1);
	if (gui->keys & (1 << KP_zoom_in))
		zoom(&gui->cam, 1);
	else if (gui->keys & (1 << KP_zoom_out))
		zoom(&gui->cam, -1);
	move(gui);
}

int	render(t_gui *gui)
{
	double ZBuffer[SCRWIDTH];

	if (gui->rendered && !gui->keys)
		return (0);
	key_render(gui);
	erase(gui->buffer);
	floor_cast(gui);
	wall_cast(gui, ZBuffer);
	sprite_cast(gui, ZBuffer);
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	gui->rendered = 1;
	return (0);
}
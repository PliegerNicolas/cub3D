/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/07/08 05:53:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "graphics.h"
/*
static void	update_speed(double *current, double target, double rate)
{
	if (target < 0.0)
	{
		if (*current - rate > target)
			*current -= rate;
		else
			*current = target;
	}
	else if (target > 0.0)
	{
		if (*current + rate < target)
			*current += rate;
		else
			*current = target;
	}
	else if (target == 0.0)
	{
		if  (*current - rate > target)
			*current -= rate;
		else if (*current + rate < target)
			*current += rate;
		else
			*current = target;
	}
}

static void	key_render(t_gui *gui)
{
	double	multiplicator;

	// Decelerate progressively if no button pressed.
	if (!gui->keys)
	{
		update_speed(&gui->cam.speed.x, 0, gui->cam.acceleration_rate.x * 1.5);
		update_speed(&gui->cam.speed.y, 0, gui->cam.acceleration_rate.y * 1.5);
	}

	// If sprinting
	if (gui->keys & (1 << KP_sprint))
		multiplicator = 1.5;
	else
		multiplicator = 1.0;

	// Accelerate until target speed while moving forth or back. Else, slow down on target axis.
	if (gui->keys & (1 << KP_forth))
		update_speed(&gui->cam.speed.x, gui->cam.speed_target.x * multiplicator,
			gui->cam.acceleration_rate.x);
	else if (gui->keys & (1 << KP_back))
		update_speed(&gui->cam.speed.x, -gui->cam.speed_target.x * multiplicator,
			gui->cam.acceleration_rate.x);
	else
		update_speed(&gui->cam.speed.x, 0, gui->cam.acceleration_rate.x * 1.5);

	// Accelerate until target speed while moving left or right. Else, slow down on target axis.
	if (gui->keys & (1 << KP_right))
		update_speed(&gui->cam.speed.y, gui->cam.speed_target.y * multiplicator,
			gui->cam.acceleration_rate.y);
	else if (gui->keys & (1 << KP_left))
		update_speed(&gui->cam.speed.y, -gui->cam.speed_target.y * multiplicator,
			gui->cam.acceleration_rate.y);
	else
		update_speed(&gui->cam.speed.y, 0, gui->cam.acceleration_rate.y * 1.5);

	// Rotate camera left or right
	if (gui->keys & (1 << KP_rot_left))
		rotate(&gui->cam, 1);
	else if (gui->keys & (1 << KP_rot_right))
		rotate(&gui->cam, -1);

	// Rotate camera up or down
	if (gui->keys & (1 << KP_rot_up))
		pitch(&gui->cam, 1);
	else if (gui->keys & (1 << KP_rot_down))
		pitch(&gui->cam, -1);

	move(gui);
}
*/

int	render(t_gui *gui)
{
	double ZBuffer[SCRWIDTH];

	if (gui->rendered && gui->cam.rndr < SPRITES)
		return (0);
	key_render(gui);
	erase(gui->buffer);
	if (gui->cam.rndr == FLOORCEIL)
		floor_cast(gui);
	wall_cast(gui, ZBuffer);
	if (gui->cam.rndr >= SPRITES)
	{
		sprite_cast(gui, ZBuffer);
		weapon(gui);
	}
	minimap(gui);
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	gui->rendered = 1;
	return (0);
}

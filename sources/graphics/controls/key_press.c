/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 05:50:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/08 09:11:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	act_on_sprint(t_gui *gui)
{
	if (gui->keys & (1 << KP_sprint))
		gui->cam.sprint_multiplicator = 2;
	else
		gui->cam.sprint_multiplicator = 1;
}

static void	act_on_move(t_gui *gui)
{
	t_play	*p;

	p = &gui->cam;
	if (gui->keys & (1 << KP_forth))
		update_speed(&p->speed.x, p->speed_target.x * p->sprint_multiplicator,
			p->acceleration_rate.x);
	else if (gui->keys & (1 << KP_back))
		update_speed(&p->speed.x, -p->speed_target.x * p->sprint_multiplicator,
			p->acceleration_rate.x);
	else
		update_speed(&gui->cam.speed.x, 0, gui->cam.acceleration_rate.x * 1.5);
	if (gui->keys & (1 << KP_right))
		update_speed(&p->speed.y, p->speed_target.y * p->sprint_multiplicator,
			p->acceleration_rate.y);
	else if (gui->keys & (1 << KP_left))
		update_speed(&p->speed.y, -p->speed_target.y * p->sprint_multiplicator,
			p->acceleration_rate.y);
	else
		update_speed(&gui->cam.speed.y, 0, gui->cam.acceleration_rate.y * 1.5);
}

static void	act_on_camera_rotation(t_gui *gui)
{
	if (gui->keys & (1 << KP_rot_left))
		rotate(&gui->cam, 1);
	else if (gui->keys & (1 << KP_rot_right))
		rotate(&gui->cam, -1);
	if (gui->keys & (1 << KP_rot_up))
		pitch(&gui->cam, 1);
	else if (gui->keys & (1 << KP_rot_down))
		pitch(&gui->cam, -1);
}

static void	act_on_zoom(t_gui *gui)
{
	(void)gui;
}

void	key_render(t_gui *gui)
{
	if (!gui->keys)
	{
		update_speed(&gui->cam.speed.x, 0, gui->cam.acceleration_rate.x * 1.5);
		update_speed(&gui->cam.speed.y, 0, gui->cam.acceleration_rate.y * 1.5);
	}
	else
	{
		act_on_sprint(gui);
		act_on_move(gui);
		act_on_camera_rotation(gui);
		act_on_zoom(gui);
	}
	move(gui);
}

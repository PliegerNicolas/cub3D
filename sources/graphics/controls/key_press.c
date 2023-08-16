/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 05:50:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/16 17:05:39 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	slow_down(t_gui *gui)
{
	update_speed(&gui->cam.speed.x, 0, gui->cam.accel_rate.x * 1.5);
	update_speed(&gui->cam.speed.y, 0, gui->cam.accel_rate.y * 1.5);
	gui->cam.rot_speed.x = 0;
	gui->cam.rot_speed.y = 0;
	act_on_sprint(gui);
}

static void	speed_up(t_gui *gui)
{
	act_on_sprint(gui);
	act_on_move(gui);
	act_on_camera_rotation(gui, &gui->cam);
	act_on_zoom(gui);
}

void	key_render(t_gui *gui)
{
	if (!nextframe(RATE_MOVE))
		return ;
	else if (!gui->keys)
		slow_down(gui);
	else
		speed_up(gui);
	act_on_toggles(gui);
	move(gui);
}

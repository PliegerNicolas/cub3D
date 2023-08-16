/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 05:50:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/16 16:50:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	act_on_sprint(t_gui *gui)
{
	static bool	cooldown;

	if (gui->keys & (1 << KP_sprint) && !cooldown)
		gui->cam.sprint_multiplicator = 2;
	else
		gui->cam.sprint_multiplicator = 1;
	if (!nextframe(RATE_SPRINT))
		return ;
	if (gui->cam.sprint_multiplicator == 2)
		gui->cam.stat.get[STA] -= 2 * (gui->cam.stat.get[STA] > 0)
			* (magnitude(gui->cam.speed) > 0);
	else
		gui->cam.stat.get[STA] += (2 - cooldown)
			* (gui->cam.stat.get[STA] < gui->cam.stat.max[STA]);
	if (gui->cam.stat.get[STA] <= 0)
		cooldown = 1;
	if (cooldown && gui->cam.stat.get[STA] == gui->cam.stat.max[STA])
		cooldown = 0;
}

static void	act_on_move(t_gui *gui)
{
	t_play	*p;

	p = &gui->cam;
	if (gui->keys & (1 << KP_forth))
		update_speed(&p->speed.x, p->speed_target.x * p->sprint_multiplicator,
			p->accel_rate.x);
	else if (gui->keys & (1 << KP_back))
		update_speed(&p->speed.x, -p->speed_target.x * p->sprint_multiplicator,
			p->accel_rate.x);
	else
		update_speed(&gui->cam.speed.x, 0, gui->cam.accel_rate.x * 1.5);
	if (gui->keys & (1 << KP_right))
		update_speed(&p->speed.y, p->speed_target.y * p->sprint_multiplicator,
			p->accel_rate.y);
	else if (gui->keys & (1 << KP_left))
		update_speed(&p->speed.y, -p->speed_target.y * p->sprint_multiplicator,
			p->accel_rate.y);
	else
		update_speed(&gui->cam.speed.y, 0, gui->cam.accel_rate.y * 1.5);
}

static void	act_on_camera_rotation(t_gui *gui, t_play *p)
{
	if (gui->keys & (1 << KP_rot_left))
	{
		update_rotation_speed(&p->rot_speed.x, p->rot_speed_target.x,
			p->rot_accel_rate.x, 1);
		rotate(p, 1);
	}
	else if (gui->keys & (1 << KP_rot_right))
	{
		update_rotation_speed(&p->rot_speed.x, -p->rot_speed_target.x,
			p->rot_accel_rate.x, -1);
		rotate(p, 1);
	}
	if (gui->keys & (1 << KP_rot_up))
	{
		update_rotation_speed(&p->rot_speed.y, p->rot_speed_target.y,
			p->rot_accel_rate.y, 1);
		pitch(p, 1);
	}
	else if (gui->keys & (1 << KP_rot_down))
	{
		update_rotation_speed(&p->rot_speed.y, -p->rot_speed_target.y,
			p->rot_accel_rate.y, -1);
		pitch(p, 1);
	}
}

static void	act_on_zoom(t_gui *gui)
{
	if (gui->keys & (1 << KP_zoom_in))
		zoom(&gui->cam, 1);
	if (gui->keys & (1 << KP_zoom_out))
		zoom(&gui->cam, -1);
}

void	key_render(t_gui *gui)
{
	if (!nextframe(RATE_MOVE))
		return ;
	else if (!gui->keys)
	{
		update_speed(&gui->cam.speed.x, 0, gui->cam.accel_rate.x * 1.5);
		update_speed(&gui->cam.speed.y, 0, gui->cam.accel_rate.y * 1.5);
		gui->cam.rot_speed.x = 0;
		gui->cam.rot_speed.y = 0;
		act_on_sprint(gui);
	}
	else
	{
		act_on_sprint(gui);
		act_on_move(gui);
		act_on_camera_rotation(gui, &gui->cam);
		act_on_zoom(gui);
	}
	if (check_press((gui->keys & (1 << KP_interact)) != 0, 0))
		interact(gui);
	if (check_press((gui->keys & (1 << KP_map)) != 0, 1))
	{
		select_map_type(&gui->cam.rndr);
		gui->rendered = 0;
	}
	if (check_press((gui->keys & (1 << KP_statistics)) != 0, 2))
	{
		toggle_mask(&gui->cam.rndr, STATISTICS, TOGGLE);
		gui->rendered = 0;
	}
	move(gui);
}

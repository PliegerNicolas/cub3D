/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_on_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:57:55 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/16 16:58:22 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	act_on_camera_rotation(t_gui *gui, t_play *p)
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

void	act_on_zoom(t_gui *gui)
{
	if (gui->keys & (1 << KP_zoom_in))
		zoom(&gui->cam, 1);
	if (gui->keys & (1 << KP_zoom_out))
		zoom(&gui->cam, -1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_projectile_obstructed.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:50:23 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/12 13:47:47 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	is_in_fov(t_play *player, t_rc *rc)
{
	double	angle_diff;
	double	angle_player;
	double	angle_ray;

	if (player->pitch > 0.5 || player->pitch < -0.5)
		return (false);
	angle_player = atan2(player->dir.y, player->dir.x);
	angle_ray = atan2(rc->ray_dir.y, rc->ray_dir.x);
	angle_diff = fabs(angle_player - angle_ray);
	if (angle_diff > 0.6)
		return (false);
	return (true);
}

static void	rays(t_play *p, t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_dist.x = (p->posi.x - rc->map_x) * rc->delta_dist.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist.x = (rc->map_x + 1.0 - p->posi.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_dist.y = (p->posi.y - rc->map_y) * rc->delta_dist.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist.y = (rc->map_y + 1.0 - p->posi.y) * rc->delta_dist.y;
	}
}

static bool	cast(t_gui *gui, t_rc *rc, t_vect *target_position)
{
	rays(&gui->cam, rc);
	while (true)
	{
		if (is_out_of_bounds(gui, rc->map_x, rc->map_y))
			return (false);
		if (wall_collision(gui, rc->map_x, rc->map_y))
			return (false);
		if (is_target_position_found(*target_position, rc->map_x, rc->map_y))
			return (true);
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map_x += rc->step_x;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map_y += rc->step_y;
		}
	}
}

bool	is_projectile_obstructed(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;

	rc.map_x = (int)gui->cam.posi.x;
	rc.map_y = (int)gui->cam.posi.y;
	rc.ray_dir.x = (projectile->posi.x - gui->cam.posi.x) * gui->cam.zoom;
	rc.ray_dir.y = (projectile->posi.y - gui->cam.posi.y) * gui->cam.zoom;
	if (!is_in_fov(&gui->cam, &rc))
		return (true);
	rc.delta_dist.x = inv_safe(rc.ray_dir.x);
	rc.delta_dist.y = inv_safe(rc.ray_dir.y);
	if (!cast(gui, &rc, &projectile->posi))
		return (true);
	return (false);
}

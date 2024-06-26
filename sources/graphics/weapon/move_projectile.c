/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_projectile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:49:53 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/14 15:05:51 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	rays(t_vect target_pos, t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_dist.x = (target_pos.x - rc->map_x) * rc->delta_dist.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist.x = (rc->map_x + 1.0 - target_pos.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_dist.y = (target_pos.y - rc->map_y) * rc->delta_dist.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist.y = (rc->map_y + 1.0 - target_pos.y) * rc->delta_dist.y;
	}
}

static bool	cast(t_gui *gui, t_rc *rc, t_vect *target_position)
{
	rays(*target_position, rc);
	while (true)
	{
		if (is_out_of_bounds(gui, rc->map_x, rc->map_y))
			return (false);
		if (wall_collision(gui, rc->map_x, rc->map_y)
			|| sprite_collision(gui, rc->map_x, rc->map_y))
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

t_vect	target_projectile_position(t_prj *projectile)
{
	t_vect	next_pos;

	next_pos.x = projectile->posi.x
		+ projectile->direction.x * (double)PROJECTILE_SPEED;
	next_pos.y = projectile->posi.y
		+ projectile->direction.y * (double)PROJECTILE_SPEED;
	return (next_pos);
}

bool	move_projectile(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;
	t_vect	target_position;

	target_position = target_projectile_position(projectile);
	rc.map_x = (int)projectile->posi.x;
	rc.map_y = (int)projectile->posi.y;
	rc.ray_dir.x = target_position.x - projectile->posi.x;
	rc.ray_dir.y = target_position.y - projectile->posi.y;
	rc.delta_dist.x = inv_safe(rc.ray_dir.x);
	rc.delta_dist.y = inv_safe(rc.ray_dir.y);
	projectile->posi.x = target_position.x;
	projectile->posi.y = target_position.y;
	if (cast(gui, &rc, &target_position))
		return (true);
	return (false);
}

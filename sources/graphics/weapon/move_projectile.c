/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_projectile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:49:53 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/11 12:28:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

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
		int	cell_x = (int)rc->map_x;
		int	cell_y = (int)rc->map_y;
		if (cell_x < 0 || cell_x >= (int)gui->map.width || cell_y < 0
			|| cell_y >= (int)gui->map.height)
			return (false);
		if (cell_x == (int)target_position->x && cell_y == (int)target_position->y)
			return (true);
		if (gui->map.map[cell_x][cell_y] % DOOR_OPEN != floor_tile)
			return (false);
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
	next_pos.x = projectile->posi.x + (double)PROJECTILE_SPEED * projectile->direction.x;
	next_pos.y = projectile->posi.y + (double)PROJECTILE_SPEED * projectile->direction.y;
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

	if (cast(gui, &rc, &target_position))
	{
		projectile->posi.x = target_position.x;
		projectile->posi.y = target_position.y;
		return (true);
	}
	else
	{
		projectile->posi.x = projectile->posi.x + rc.side_dist.x * rc.ray_dir.x;
		projectile->posi.y = projectile->posi.y + rc.side_dist.y * rc.ray_dir.y;
		return (false);
    }
}

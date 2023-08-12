/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_projectile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:49:53 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/12 12:44:47 by nicolas          ###   ########.fr       */
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

		printf("rc->map_x = %d, rc->map_y = %d\n", rc->map_x, rc->map_y);

		if (is_out_of_bounds(gui, cell_x, cell_y))
			return (false);
		if (wall_collision(gui, cell_x, cell_y) || sprite_collision(gui, cell_x, cell_y))
			return (false);
		if (is_target_position_found(*target_position, cell_x, cell_y))
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
	next_pos.x = projectile->posi.x + (double)PROJECTILE_SPEED * projectile->direction.x;
	next_pos.y = projectile->posi.y + (double)PROJECTILE_SPEED * projectile->direction.y;
	return (next_pos);
}

static bool	calc_hit_distance(t_rc *rc, t_prj *projectile)
{
	double	hit_distance;

	if (rc->side_dist.y < rc->side_dist.x)
		hit_distance = (rc->map_y - projectile->posi.y
			+ (1 - rc->step_y) / 2) / rc->ray_dir.y;
	else
		hit_distance = (rc->map_x - projectile->posi.x
			+ (1 - rc->step_x) / 2) / rc->ray_dir.x;
	return (hit_distance);
}

bool	move_projectile(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;
	t_vect	target_position;
	double	hit_distance;

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
		hit_distance = calc_hit_distance(&rc, projectile);
        projectile->posi.x = projectile->posi.x + rc.ray_dir.x * hit_distance;
        projectile->posi.y = projectile->posi.y + rc.ray_dir.y * hit_distance;
		return (false);
    }
}

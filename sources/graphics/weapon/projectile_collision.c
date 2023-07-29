/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:36:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/29 16:00:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	is_max_distance_reached(t_gui *gui, t_prj *projectile)
{
	t_play	*player;
	double	proj_ray_dir_x;
	double	proj_ray_dir_y;
	double	distance;

	player = &gui->cam;
	proj_ray_dir_x = projectile->posi.x - player->posi.x;
	proj_ray_dir_y = projectile->posi.y - player->posi.y;
	distance = sqrt(proj_ray_dir_x * proj_ray_dir_x
			+ proj_ray_dir_y * proj_ray_dir_y);
	if (distance >= PROJECTILE_MAX_DISTANCE)
		return (true);
	return (false);
}

static bool	hit_map(int **map, t_prj *projectile)
{
	if (map[(int)projectile->posi.x][(int)projectile->posi.y]
		% DOOR_OPEN != floor_tile)
		return (true);
	else if (projectile->posi.z <= -1.0 || projectile->posi.z >= 1.0)
		return (true);
	return (false);
}

static bool	hit_mob(t_gui *gui, t_prj *projectile)
{
	t_sprt	*sprt;
	size_t	i;

	i = 0;
	while (i < (size_t)gui->textures.spnb)
	{
		sprt = &gui->textures.sprites[i];
		if (sprt->type != DEAD)
		{
			if (projectile->posi.z < -0.2 && projectile->posi.z > 0.0)
				return (false);
			else if (sprt->posi.x - 0.25 < projectile->posi.x
				&& sprt->posi.x + 0.25 > projectile->posi.x
				&& sprt->posi.y - 0.25 < projectile->posi.y
				&& sprt->posi.y + 0.25 > projectile->posi.y)
				return (sprt->type = DEAD, true);
		}
		i++;
	}
	return (false);
}

bool	projectile_collision(t_gui *gui, t_prj *projectile)
{
	if (hit_map(gui->map.map, projectile))
		return (true);
	else if (hit_mob(gui, projectile))
		return (true);
	else if (is_max_distance_reached(gui, projectile))
		return (true);
	return (false);
}

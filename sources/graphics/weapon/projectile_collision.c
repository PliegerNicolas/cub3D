/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:36:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/11 09:49:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	hit_map(int **map, t_prj *projectile)
{
	if (map[(int)projectile->posi.x][(int)projectile->posi.y]
		% DOOR_OPEN != floor_tile)
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
			if (sprt->posi.x - 0.20 < projectile->posi.x
				&& sprt->posi.x + 0.20 > projectile->posi.x
				&& sprt->posi.y - 0.20 < projectile->posi.y
				&& sprt->posi.y + 0.20 > projectile->posi.y)
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
	return (false);
}

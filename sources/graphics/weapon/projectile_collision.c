/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:36:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/15 11:58:21 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

bool	is_out_of_bounds(t_gui *gui, int cell_x, int cell_y)
{
	if (cell_x < 0 || cell_x >= (int)gui->map.height)
		return (true);
	if (cell_y < 0 || cell_y >= (int)gui->map.width)
		return (true);
	return (false);
}

bool	wall_collision(t_gui *gui, int cell_x, int cell_y)
{
	int	**map;

	map = gui->map.map;
	if (map[cell_x][cell_y] % DOOR_OPEN != floor_tile)
		return (true);
	return (false);
}

bool	is_target_position_found(t_vect target_position, int cell_x, int cell_y)
{
	if (cell_x == (int)target_position.x && cell_y == (int)target_position.y)
		return (true);
	return (false);
}

bool	sprite_collision(t_gui *gui, int cell_x, int cell_y)
{
	t_sprt	*sprt;
	t_vect	sprt_pos;

	sprt = gui->textures.sprites;
	while (sprt)
	{
		if (sprt->type == ALIVE)
		{
			sprt_pos = sprt->posi;
			if ((int)sprt_pos.x == cell_x && (int)sprt_pos.y == cell_y)
			{
				sprt->type = DEAD;
				return (true);
			}
		}
		sprt = sprt->next;
	}
	return (false);
}

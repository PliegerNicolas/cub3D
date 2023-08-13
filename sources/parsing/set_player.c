/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:15:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/13 12:38:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static bool	is_spawn_point(int val)
{
	if (val == spawn_north_tile || val == spawn_south_tile
		|| val == spawn_west_tile || val == spawn_east_tile)
		return (true);
	return (false);
}

static void	set_base_stats(t_play *player)
{
	player->speed.x = 0;
	player->speed.y = 0;
	player->speed_target.x = 0.075;
	player->speed_target.y = 0.075;
	player->rot_speed.x = 0.0;
	player->rot_speed.y = 0.0;
	player->rot_speed_target.x = 0.05;
	player->rot_speed_target.y = 0.03;
	player->accel_rate.x = player->speed_target.x * 0.1;
	player->accel_rate.y = player->speed_target.y * 0.1;
	player->rot_accel_rate.x = player->rot_speed_target.x * 0.15;
	player->rot_accel_rate.y = player->rot_speed_target.y * 0.15;
	player->sprint_multiplicator = 2.0;
	player->pitch = 0.0;
	player->dark = 0;
	player->zoom = 1;
	player->zoom_rate = 0.025;
	player->hit_box.x = 0.1;
	player->hit_box.y = 0.1;
	player->rndr = 0b111;
}

static void	set_vector(t_play *player, size_t row, size_t col)
{
	t_vect	pos;

	pos.x = row;
	pos.y = col;
	player->posi = pos;
	player->stat.get[HP] = 100;
	player->stat.get[STA] = 50;
	player->stat.get[ARM] = 0;
	player->stat.get[XP] = 0;
	player->stat.get[LVL] = 0;
	player->stat.max[HP] = 100;
	player->stat.max[STA] = 50;
	player->stat.max[ARM] = 100;
	player->stat.max[XP] = 100;
	player->stat.max[LVL] = 100;
}

static void	set_orientation(t_play *player, int val)
{
	if (val == spawn_north_tile)
	{
		player->dir = (t_vect){-1, 0};
		player->plane = (t_vect){0, 0.66};
	}
	else if (val == spawn_south_tile)
	{
		player->dir = (t_vect){1, 0};
		player->plane = (t_vect){0, -0.66};
	}
	else if (val == spawn_west_tile)
	{
		player->dir = (t_vect){0, -1};
		player->plane = (t_vect){-0.66, 0};
	}
	else if (val == spawn_east_tile)
	{
		player->dir = (t_vect){0, 1};
		player->plane = (t_vect){0.66, 0};
	}
	player->pitch = 0.0;
}

bool	set_player(t_gui *gui)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < gui->map.height)
	{
		col = 0;
		while (col < gui->map.width)
		{
			if (is_spawn_point(gui->map.map[row][col]))
			{
				set_base_stats(&gui->cam);
				set_vector(&gui->cam, row, col);
				set_orientation(&gui->cam, gui->map.map[row][col]);
				gui->map.map[row][col] = 0;
				return (false);
			}
			col++;
		}
		row++;
	}
	return (put_parsing_err("No spawn point found in map."), true);
}

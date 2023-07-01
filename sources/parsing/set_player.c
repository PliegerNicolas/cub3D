/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:15:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/02 01:32:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	is_spawn_point(int val)
{
	if (val == 2 || val == 3 || val == 4 || val == 5)
		return (true);
	return (false);
}

static void	set_base_stats(t_play *player)
{
	player->pitch = 0;
	player->zoom = 1;
	player->speed = 1;
	player->rndr = FLOORCEIL;
}

static void	set_vector(t_play *player, size_t row, size_t col)
{
	t_vect	pos;

	pos.x = col;
	pos.y = row;
	player->posi = pos;
}

static void	set_orientation(t_play *player, int val)
{
	if (val == 2)
	{
		player->dir = (t_vect){-1, 0};
		player->plane = (t_vect){0, 0.66};
	}
	else if (val == 3)
	{
		player->dir = (t_vect){1, 0};
		player->plane = (t_vect){0, -0.66};
	}
	else if (val == 4)
	{
		player->dir = (t_vect){0, 1};
		player->plane = (t_vect){0.66, 0};
	}
	else if (val == 5)
	{
		player->dir = (t_vect){0, -1};
		player->plane = (t_vect){-0.66, 0};
	}
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
				gui->map.map[row][col] = 0;
				set_base_stats(&gui->cam);
				set_vector(&gui->cam, row, col);
				set_orientation(&gui->cam, gui->map.map[row][col]);
				return (false);
			}
			col++;
		}
		row++;
	}
	return (put_parsing_err("No spawn point found in map."), true);
}

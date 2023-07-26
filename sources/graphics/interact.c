/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:02:07 by emis              #+#    #+#             */
/*   Updated: 2023/07/25 14:38:22 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

bool	check_press(bool press, size_t i)
{
	static bool	last[42];

	if (press != last[i])
		return (last[i] = press, press);
	return (false);
}

int	interact(t_gui *gui)
{
	int		map_x;
	int		map_y;
	int		i;
	int		j;

	map_x = (int)gui->cam.posi.x;
	map_y = (int)gui->cam.posi.y;
	i = map_x - (map_x > 0) - 1;
	while (++i < map_x + 2)
	{
		j = map_y - (map_y > 0) - 1;
		while (++j < map_y + 2)
		{
			if (gui->map.map[bind(i, 0, gui->map.height)]
				[bind(j, 0, gui->map.width)] == DOOR_CLOSED)
				gui->map.map[bind(i, 0, gui->map.height)]
				[bind(j, 0, gui->map.width)] = DOOR_OPEN;
			else if (gui->map.map[bind(i, 0, gui->map.height)]
				[bind(j, 0, gui->map.width)] == DOOR_OPEN
				&& ((int)gui->cam.posi.x != i || (int)gui->cam.posi.y != j))
				gui->map.map[bind(i, 0, gui->map.height)]
				[bind(j, 0, gui->map.width)] = DOOR_CLOSED;
		}
	}
	return (gui->rendered = 0, 0);
}
/*
// printf("--[%d|%d]==\n", mapX, mapY);
//printf("[%d|%d]->%d\n", i, j,
	gui->map.map[j % gui->map.height][i % gui->map.width])
*/

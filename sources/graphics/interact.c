/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:02:07 by emis              #+#    #+#             */
/*   Updated: 2023/07/16 07:18:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

// proof of concept
int	interact(t_gui *gui)
{
	int		map_x;
	int		map_y;
	int		i;
	int		j;

	map_x = (int)gui->cam.posi.x;
	map_y = (int)gui->cam.posi.y;
	i = map_x - (map_x > 0);
	while (i < map_x + 2)
	{
		j = map_y - (map_y > 0);
		while (j < map_y + 2)
		{
			if (gui->map.map[bind(i, 0, gui->map.height)]
				[bind(j, 0, gui->map.width)] == DOOR_CLOSED)
				gui->map.map[bind(i, 0, gui->map.height)]
				[bind(j, 0, gui->map.width)] = DOOR_OPEN;
			j++;
		}
		i++;
	}
	return (0);
}
/*
// printf("--[%d|%d]==\n", mapX, mapY);
//printf("[%d|%d]->%d\n", i, j,
	gui->map.map[j % gui->map.height][i % gui->map.width])
*/

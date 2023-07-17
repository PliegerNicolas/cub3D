/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:02:07 by emis              #+#    #+#             */
/*   Updated: 2023/07/17 18:24:57 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "graphics.h"

// proof of concept
int	interact(t_gui *gui)
{
	int	mapX;
	int	mapY;
	int	x;
	int	y;

	mapX = (int)gui->cam.posi.x;
	mapY = (int)gui->cam.posi.y;
	x = mapX - (mapX > 0) - 1;
	while (++x < mapX + 2)
	{
		y = mapY - (mapY > 0) - 1;
		while (++y < mapY + 2)
		{
			if (gui->map.map[bind(x, 0, gui->map.height)][bind(y, 0, gui->map.width)] == DOOR_CLOSED)
				gui->map.map[bind(x, 0, gui->map.height)][bind(y, 0, gui->map.width)] = DOOR_OPEN;
			else if (gui->map.map[bind(x, 0, gui->map.height)][bind(y, 0, gui->map.width)] == DOOR_OPEN
				&& ((int)gui->cam.posi.x != x || (int)gui->cam.posi.y != y))
				gui->map.map[bind(x, 0, gui->map.height)][bind(y, 0, gui->map.width)] = DOOR_CLOSED;
		}
	}
	return (0);
}
	// printf("--[%d|%d]==\n", mapX, mapY);
//printf("[%d|%d]->%d\n", i, j, gui->map.map[j % gui->map.height][i % gui->map.width]), 
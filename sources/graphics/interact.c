/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:02:07 by emis              #+#    #+#             */
/*   Updated: 2023/07/15 16:45:51 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "graphics.h"

// proof of concept
int	interact(t_gui *gui)
{
	int	mapX;
	int	mapY;

	mapX = (int)gui->cam.posi.x;
	mapY = (int)gui->cam.posi.y;
	for (int i=mapX - (mapX > 0); i < mapX + 2; i++)
		for (int j=mapY - (mapY > 0); j < mapY + 2; j++ )
			if (gui->map.map[bind(i, 0, gui->map.height)][bind(j, 0, gui->map.width)] == DOOR_CLOSED)
				gui->map.map[bind(i, 0, gui->map.height)][bind(j, 0, gui->map.width)] = DOOR_OPEN;
	return (0);
}
	// printf("--[%d|%d]==\n", mapX, mapY);
//printf("[%d|%d]->%d\n", i, j, gui->map.map[j % gui->map.height][i % gui->map.width]), 
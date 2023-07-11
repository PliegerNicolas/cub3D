/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:02:07 by emis              #+#    #+#             */
/*   Updated: 2023/07/11 18:41:51 by emis             ###   ########.fr       */
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
	printf("--[%d|%d]==\n", mapX, mapY);
	for (int i=mapX - (mapX > 0); i < mapX + 2; i++)
		for (int j=mapY - (mapY > 0); j < mapY + 2; j++ )
			if (printf("[%d|%d]->%d\n", i, j, gui->map.map[i % gui->map.width][j % gui->map.height]), gui->map.map[i % gui->map.width][j % gui->map.height] == DOOR_CLOSED)
				gui->map.map[i % gui->map.width][j % gui->map.height] = DOOR_OPEN;
	return (0);
}
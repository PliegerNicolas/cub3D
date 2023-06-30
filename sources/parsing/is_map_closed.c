/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 06:16:20 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/30 15:58:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	flood_fill(int **map, size_t row, size_t col,
	size_t rowsize, size_t colsize)
{
	(void)map;
	(void)row;
	(void)col;
	(void)rowsize;
	(void)colsize;
	return (true);
}

bool	is_map_closed(const t_gui *gui)
{
	int	**map;
	int	row;
	int	col;

	if (!gui || !(gui->map.map))
		return (true);
	row = (int)gui->cam.posi.y;
	col = (int)gui->cam.posi.x;
	map = copy_int_arr(gui->map.map, gui->map.height, gui->map.width);
    if (map == NULL)
        return (put_parsing_err("Not enough memory."), true);
    //if (flood_fill((t_gui*)gui, row, col))
        //return (free_int_arr(map, gui->map.height), false);
	printf("%d\n", flood_fill(map, row, col, gui->map.height, gui->map.width));
	return (free_int_arr(map, gui->map.height), true);
}

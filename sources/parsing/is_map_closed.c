/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 06:16:20 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/02 06:18:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

/*
static void	put_map(int **map, size_t rowsize, size_t colsize)
{
	size_t		row;
	size_t		col;

	row = 0;
	while (row < rowsize)
	{
		col = 0;
		while (col < colsize)
		{
			if (map[row][col] == -1 || map[row][col] == -2)
				printf(" ");
			else
				printf("%d", map[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}
*/

static bool	flood_fill(const t_gui *gui, int **map, size_t row, size_t col)
{
	bool	result;
	size_t	rowsize;
	size_t	colsize;

	rowsize = gui->map.height;
	colsize = gui->map.width;
	if ((row == 0 || col == 0 || row >= rowsize - 1 || col >= colsize - 1)
		&& map[row][col] != 1)
		return (false);
	if (map[row][col] == 1)
		return (true);
	map[row][col] = -2;
	result = true;
	if (row > 0 && map[row - 1][col] != -2)
		result &= flood_fill(gui, map, row - 1, col);
	if (row + 1 < rowsize && map[row + 1][col] != -2)
		result &= flood_fill(gui, map, row + 1, col);
	if (col > 0 && map[row][col - 1] != -2)
		result &= flood_fill(gui, map, row, col - 1);
	if (col + 1 < colsize && map[row][col + 1] != -2)
		result &= flood_fill(gui, map, row, col + 1);
	return (result);
}

bool	is_map_closed(const t_gui *gui)
{
	int	**map;
	int	row;
	int	col;

	if (!gui || !(gui->map.map))
		return (true);
	row = gui->cam.posi.x;
	col = gui->cam.posi.y;
	map = copy_int_arr(gui->map.map, gui->map.height, gui->map.width);
	if (!map)
		return (put_parsing_err("Not enough memory."), true);
	if (!flood_fill(gui, map, row, col))
	{
		put_parsing_err("Map isn't closed around the player's spawn point.");
		return (free_int_arr(map, gui->map.height), false);
	}
	return (free_int_arr(map, gui->map.height), true);
}

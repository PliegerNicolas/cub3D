/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:34 by emis              #+#    #+#             */
/*   Updated: 2023/07/11 18:55:29 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"
# include "../../includes/parsing.h"

# define MINISIZE 10
# define BLACK 0xAA010101
# define WHITE 0xAAFFFFFF
# define GREY 0xAAAAAAAA
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define MAG 0xFF11FF
# define MAGF 0xEEFF4444

static void	dot(t_img *img, int px, int py, int color)
{
	int	x;
	int	y;

	y = py - 3;
	while (++y < py + 3)
	{
		x = px - 3;
		while (++x < px + 3)
			pixput(img, x, y, color);
	}
}

static int	color_from_tile(t_maptile tile)
{
	if (tile == 1)
		return (BLACK);
	else if (tile == 0)
		return (WHITE);
	else if (tile == DOOR_OPEN)
		return (GREEN);
	else if (tile == DOOR_CLOSED)
		return (RED);
	return (0x01000000);
}

void	minimap(t_gui *gui)
{
	size_t	x;
	size_t	y;
	size_t	size;

	size = gui->map.height * gui->map.width / 100;
	x = 0;
	while (x < gui->map.height * size)
	{
		y = 0;
		while (y < gui->map.width * size)
		{
			pixput(gui->buffer, y, x,
				color_from_tile(gui->map.map[x / size][y / size]));
			y++;
		}
		x++;
	}
	dot(gui->buffer, gui->cam.posi.y * size,
		gui->cam.posi.x * size, MAG);
	dot(gui->buffer, gui->cam.posi.y * size + gui->cam.dir.y * 4,
		gui->cam.posi.x * size + gui->cam.dir.x * 4, MAGF);
	y = -1;
	while (++y < (size_t)gui->textures.spnb)
		dot(gui->buffer, gui->textures.sprites[y].posi.y * size,
			gui->textures.sprites[y].posi.x * size, GREEN);
}

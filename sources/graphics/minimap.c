/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:34 by emis              #+#    #+#             */
/*   Updated: 2023/07/16 15:53:01 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

# define BLACK 0x010101
# define WHITE 0xFFFFFF
# define GREY 0xAAAAAA
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

static void	draw_entities_on_map(t_gui *gui, size_t size)
{
	size_t	y;

	dot(gui->buffer, gui->cam.posi.y * size,
		gui->cam.posi.x * size, MAG);
	dot(gui->buffer, gui->cam.posi.y * size + gui->cam.dir.y * 4,
		gui->cam.posi.x * size + gui->cam.dir.x * 4, MAGF);
	y = 0;
	while (y < (size_t)gui->textures.spnb)
	{
		dot(gui->buffer, gui->textures.sprites[y].posi.y * size,
			gui->textures.sprites[y].posi.x * size, GREEN);
		y++;
	}
}

void	minimap(t_gui *gui)
{
	size_t	x;
	size_t	y;
	size_t	size;
	double	dist;

	size = 15 - (sqrt(gui->map.height * gui->map.width) / 10);
	x = 0;
	while (x < gui->map.height * size)
	{
		y = 0;
		while (y < gui->map.width * size)
		{
			// ONLY SEE AROUND THE PLAYER UP TO A CERTAIN RADIUS
			dist = magnitude((t_vect){x - gui->cam.posi.x * size, y - gui->cam.posi.y * size});
			dist *= gui->cam.dark / 20.0;
			// // // LASER
			// // dist *= angle(gui->cam.dir, delta(gui->cam.posi,
			// // (t_vect){x / (double)size, y / (double)size})) * 10;
			// FLASHLIGHT
			dist *= 1 + 100 * (angle(gui->cam.dir, delta(gui->cam.posi,
				(t_vect){x / (double)size, y / (double)size})) > 0.6);
			pixput(gui->buffer, y, x,
				color_from_tile(gui->map.map[x / size][y / size]) //);
				| (bind(0xF8 - dist * 2, 1, 255) << 24));
			y++;
		}
		x++;
	}
	draw_entities_on_map(gui, size);
}

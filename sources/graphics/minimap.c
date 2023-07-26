/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:34 by emis              #+#    #+#             */
/*   Updated: 2023/07/26 16:15:57 by emis             ###   ########.fr       */
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
# define MAGF 0xAAFF44FF

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
	return (0);
}

static void	draw_entities_on_map(t_gui *gui, size_t size)
{
	t_sprt	*sp;

	tri(gui->buffer, scale(gui->cam.posi, size),
		scale(gui->cam.dir, size * 0.8), MAGF);
	sp = gui->textures.sprites;
	while (sp)
	{
		if (sp->type == ALIVE)
			dot(gui->buffer, sp->posi.y * size,
				sp->posi.x * size, RED);
		sp = sp->next;
	}
}

void	minimap(t_gui *gui)
{
	const size_t	s = 14;
	size_t			x;
	size_t			y;

	x = -1;
	while (++x < s * s)
	{
		y = -1;
		while (++y < s * s)
		{
			// Display a circle
			if (magnitude((t_vect){x - s * s / 2.0,
				y - s * s / 2.0}) > s * s / 2)
				continue;
			pixput(gui->buffer, y, x, color_from_tile(gui->map.map
				[bind(gui->cam.posi.x * s + x - s * s / 2, 0, gui->map.height * s) / s]
				[bind(gui->cam.posi.y * s + y - s * s / 2, 0, gui->map.width * s) / s])
				| 0xAA << 24);
		}
	}
	tri(gui->buffer, (t_vect){s * s / 2, s * s / 2},
		scale(gui->cam.dir, s * 0.8), MAGF);
}

void	fullmap(t_gui *gui)
{
	int		x;
	int		y;
	int		size;
	double	dist;

	size = 15 - (sqrt(gui->map.height * gui->map.width) / 10);
	x = -1;
	while (y = -1, ++x < (int)gui->map.height * size)
	{
		while (++y < (int)gui->map.width * size)
		{
			if (!color_from_tile(gui->map.map[x / size][y / size]))
				continue;
			dist = magnitude((t_vect){x - gui->cam.posi.x * size, y - gui->cam.posi.y * size});
			dist *= gui->cam.dark / 20.0;
			dist *= 1 + 100 * (angle(gui->cam.dir, delta(gui->cam.posi,
				(t_vect){x / (double)size, y / (double)size})) > 0.66 / gui->cam.zoom);
			dist += !gui->cam.dark * 0x22;
			pixput(gui->buffer, y, x,
				color_from_tile(gui->map.map[x / size][y / size]) //);
				| (bind(0xF8 - dist * 2, 1, 255) << 24));
		}
	}
	draw_entities_on_map(gui, size);
}

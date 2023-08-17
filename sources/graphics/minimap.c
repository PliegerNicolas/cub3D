/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:34 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 19:53:54 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static int	color_from_tile(t_maptile tile)
{
	if (tile == 1)
		return (MAPBLACK);
	else if (tile == 0)
		return (MAPWHITE);
	else if (tile == DOOR_OPEN)
		return (MAPGREEN);
	else if (tile == DOOR_CLOSED)
		return (MAPRED);
	return (0);
}

static void	draw_entities_on_map(t_gui *gui, size_t size)
{
	t_sprt	*sp;

	tri(gui->buffer, scale(gui->cam.posi, size),
		scale(gui->cam.dir, size * 0.8), MAPMAGF);
	sp = gui->textures.sprites;
	while (sp)
	{
		if (sp->type == ALIVE)
			dot(gui->buffer, sp->posi.y * size,
				sp->posi.x * size, MAPRED);
		sp = sp->next;
	}
}

int	minimap(t_gui *gui, t_vect where, size_t s, bool c)
{
	size_t	x;
	size_t	y;
	t_vect	t;

	x = -1;
	while (++x < s * s)
	{
		y = -1;
		while (++y < s * s)
		{
			if (magnitude((t_vect){x - s * s / 2.0,
					y - s * s / 2.0}) > s * s / 2)
				continue ;
			t = (t_vect){x - s * s / 2.0, y - s * s / 2.0};
			t = v_add(scale(gui->cam.posi, s), v_add(scale(t, !c),
						scale(v_rot(t, gui->cam.dir), !!c)));
			pixput(gui->buffer, y + where.y, x + where.x,
				color_from_tile(gui->map.map[bind(t.x, 0, gui->map.height * s)
					/ s][bind(t.y, 0, gui->map.width * s) / s]) | 0xAA << 24);
		}
	}
	tri(gui->buffer, (t_vect){where.x + s * s / 2, where.y + s * s / 2},
		v_sub(scale(gui->cam.dir, s * 0.8 * !c), (t_vect){s * 0.8 * !!c, 0}),
		MAPMAGF);
	return (s);
}

static double	flashlight(t_gui *gui, int x, int y, int size)
{
	double	dist;

	dist = magnitude((t_vect){x - gui->cam.posi.x * size,
			y - gui->cam.posi.y * size});
	dist *= gui->cam.dark / 20.0;
	dist *= 1 + 100 * (angle(gui->cam.dir, delta(gui->cam.posi,
					(t_vect){x / (double)size, y / (double)size}))
			> 0.66 / gui->cam.zoom);
	dist += !gui->cam.dark * 0x22;
	return (dist);
}

int	fullmap(t_gui *gui, t_vect where)
{
	static int	size;
	int			x;
	int			y;
	int			color;

	color = 0;
	if (!size)
		size = 15 - (sqrt(gui->map.height * gui->map.width) / 10);
	x = -1;
	while (++x < (int)gui->map.height * size)
	{
		y = -1;
		while (++y < (int)gui->map.width * size)
		{
			if (!(y % size))
				color = color_from_tile(gui->map.map[x / size][y / size]);
			if (!color)
				continue ;
			pixput(gui->buffer, y + where.y, x + where.x, color | (bind(0xF8
						- flashlight(gui, x, y, size) * 2, 1, 255) << 24));
		}
	}
	draw_entities_on_map(gui, size);
	return (size);
}

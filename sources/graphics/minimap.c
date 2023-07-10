/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:34 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 13:45:00 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

#define MINISIZE 10
#define BLACK 0xAA010101
#define WHITE 0xAAFFFFFF
#define GREY 0xAAAAAAAA
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define MAG 0xFF11FF
#define MAGF 0xEEFF4444

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

void	minimap(t_gui *gui)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < gui->map.height * MINISIZE)
	{
		y = 0;
		while (y < gui->map.width * MINISIZE)
		{
			if (gui->map.map[x / MINISIZE][y / MINISIZE] == 1)
				pixput(gui->buffer, y, x, BLACK);
			else if (gui->map.map[x / MINISIZE][y / MINISIZE] == 0)
				pixput(gui->buffer, y, x, WHITE);
			y++;
		}
		x++;
	}
	dot(gui->buffer, gui->cam.posi.y * MINISIZE,
		gui->cam.posi.x * MINISIZE, MAG);
	dot(gui->buffer, gui->cam.posi.y * MINISIZE + gui->cam.dir.y * 4,
		gui->cam.posi.x * MINISIZE + gui->cam.dir.x * 4, MAGF);
	y = -1;
	while (++y < (size_t)gui->textures.spnb)
		dot(gui->buffer, gui->textures.sprites[y].posi.y * MINISIZE,
			gui->textures.sprites[y].posi.x * MINISIZE, GREEN);
}

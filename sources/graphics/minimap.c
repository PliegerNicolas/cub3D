/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:34 by emis              #+#    #+#             */
/*   Updated: 2023/06/22 19:48:57 by emis             ###   ########.fr       */
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

void	minimap(t_gui *gui)
{
	int	x;
	int	y;

	y = -1;
	while (++y < gui->map->height * MINISIZE)
	{
		x = -1;
		while (++x < gui->map->width * MINISIZE)
		{
			if (gui->map->map[x / MINISIZE][y / MINISIZE] == 1) //WALL
				pixput(gui->buffer, x, y, BLACK);
			else if (gui->map->map[x / MINISIZE][y / MINISIZE] == 0)//FLOOR
				pixput(gui->buffer, x, y, WHITE);
			else
				pixput(gui->buffer, x, y, BLACK);
		}
	}
	dot(gui->buffer, gui->cam.posi.x * MINISIZE,
		gui->cam.posi.y * MINISIZE, MAG);
	dot(gui->buffer, gui->cam.posi.x * MINISIZE + gui->cam.dir.x * 4,
		gui->cam.posi.y * MINISIZE + gui->cam.dir.y * 4, MAGF);
	y = -1;
	while (++y < gui->textures.spnb)
		dot(gui->buffer, gui->textures.sprites[y].posi.x * MINISIZE,
			gui->textures.sprites[y].posi.y * MINISIZE, GREEN);
}

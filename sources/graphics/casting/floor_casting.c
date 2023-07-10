/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:25:33 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 14:16:44 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	floor_cast(t_gui *gui)
{
	size_t	y;


	// Center of screen (horizon
	float	screen_center = 0.5 * SCRHEIGHT;
	// Player horizon
	float	horizon = screen_center + gui->cam.pitch;

	y = 0;
	while (y < SCRHEIGHT)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = (gui->cam.dir.x * gui->cam.zoom) - gui->cam.plane.x;
		float rayDirY0 = (gui->cam.dir.y * gui->cam.zoom) - gui->cam.plane.y;
		float rayDirX1 = (gui->cam.dir.x * gui->cam.zoom) + gui->cam.plane.x;
		float rayDirY1 = (gui->cam.dir.y * gui->cam.zoom) + gui->cam.plane.y;

		// Current y position centered on horizon
		int		p = y - horizon;

		// -1 to 1. Distance current Y from the player's horizon
		float	row_distance;
		if (p && y > horizon)
			row_distance = screen_center / p;
		else if (p && y <= horizon)
			row_distance = screen_center / -p;
		else
			row_distance = 0;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floor_step_x = row_distance * (rayDirX1 - rayDirX0) / SCRWIDTH;
		float floor_step_y = row_distance * (rayDirY1 - rayDirY0) / SCRWIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floor_x = gui->cam.posi.x + row_distance * rayDirX0;
		float floor_y = gui->cam.posi.y + row_distance * rayDirY0;

		size_t	x;

		x = 0;
		while (x < SCRWIDTH)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cell_x = (int)(floor_x);
			int cell_y = (int)(floor_y);

			// get the texture coordinate from the fractional part
			int tx = (int)(gui->textures.width * (floor_x - cell_x)) & (gui->textures.width - 1);
			int ty = (int)(gui->textures.height * (floor_y - cell_y)) & (gui->textures.height - 1);

			// Increment floor coord
			floor_x += floor_step_x;
			floor_y += floor_step_y;

			int	color;

			if (y > horizon)
			{
				// floor
				if (gui->textures.floorceil && gui->textures.floorceil[0])
					color = pixget(gui->textures.floorceil[0], gui->textures.width * ty + tx, 0);
				else
					color = gui->textures.floor_color;
				color = (color >> 1) & 8355711; // make a bit darker
			}
			else
			{
				// ceiling
				if (gui->textures.floorceil && gui->textures.floorceil[1])
					color = pixget(gui->textures.floorceil[1], gui->textures.width * ty + tx, 0);
				else
					color = gui->textures.ceil_color;
				color = (color >> 1) & 8355711; // make a bit darker
			}
			pixput(gui->buffer, x, y, color);

			x++;
		}
		y++;
	}
}

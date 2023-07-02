/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:25:33 by emis              #+#    #+#             */
/*   Updated: 2023/07/02 07:28:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/graphics.h"

void	floor_cast(t_gui *gui)
{
	//FLOOR CASTING
	for(int y = SCRHEIGHT / 2 + gui->cam.pitch; y < SCRHEIGHT; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = (gui->cam.dir.x * gui->cam.zoom) - gui->cam.plane.x;
		float rayDirY0 = (gui->cam.dir.y * gui->cam.zoom) - gui->cam.plane.y;
		float rayDirX1 = (gui->cam.dir.x * gui->cam.zoom) + gui->cam.plane.x;
		float rayDirY1 = (gui->cam.dir.y * gui->cam.zoom) + gui->cam.plane.y;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - gui->cam.pitch - SCRHEIGHT / 2; //floor looks ok with (- gui->cam.pitch) but ceiling ugly

		// Vertical position of the camera.
		float posZ = 0.5 * SCRHEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCRWIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCRWIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = gui->cam.posi.x + rowDistance * rayDirX0;
		float floorY = gui->cam.posi.y + rowDistance * rayDirY0;

		for(int x = 0; x < SCRWIDTH; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(gui->textures.width * (floorX - cellX)) & (gui->textures.width - 1);
			int ty = (int)(gui->textures.height * (floorY - cellY)) & (gui->textures.height - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int color;

			// floor
			if (gui->textures.floorceil && gui->textures.floorceil[0])
				color = pixget(gui->textures.floorceil[0], gui->textures.width * ty + tx, 0);
			else
				color = gui->textures.floor_color;
			color = (color >> 1) & 8355711; // make a bit darker
			pixput(gui->buffer, x, y, color);

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			if (gui->textures.floorceil && gui->textures.floorceil[1])
				color = pixget(gui->textures.floorceil[1], gui->textures.width * ty + tx, 0);
			else
				color = gui->textures.ceil_color;
			color = (color >> 1) & 8355711; // make a bit darker
			if (y > rowDistance)
				pixput(gui->buffer, x, SCRHEIGHT - y - 1, color);
		}
	}
}

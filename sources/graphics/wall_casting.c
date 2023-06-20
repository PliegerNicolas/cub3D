/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:41:41 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 14:13:30 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"



void	wall_cast(t_gui *gui, double ZBuffer[SCRWIDTH])
{
	for(int x = 0; x < SCRWIDTH; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)SCRWIDTH - 1; //x-coordinate in camera space
		double rayDirX = (gui->cam.dir.x * gui->cam.zoom) + gui->cam.plane.x * cameraX;
		double rayDirY = (gui->cam.dir.y * gui->cam.zoom) + gui->cam.plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)(gui->cam.posi.x);
		int mapY = (int)(gui->cam.posi.y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		//unlike (dirX, dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (gui->cam.posi.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - gui->cam.posi.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (gui->cam.posi.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - gui->cam.posi.y) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			// if (mapX >= 24 || mapX < 0 || mapY >= 24 || mapY < 0) // spawn outside map
			// 	return (gui->mlx->end_loop = 1, 42);
			//Check if ray has hit a wall
			if(gui->map->map[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);
#define SIMPLE 1

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCRHEIGHT / perpWallDist);

		// int pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch;
		if(drawEnd >= SCRHEIGHT) drawEnd = SCRHEIGHT - 1;
#if SIMPLE == 0
		(void)ZBuffer;
		//choose wall color
		int color;
		switch(gui->map->map[mapX][mapY])
		{
			case 1:  color = (255 << 16);    break; //red
			case 2:  color = (255 << 8);  break; //green
			case 3:  color = (255 << 0);   break; //blue
			case 4:  color = (255 << 16) | (255 << 8) | (255 << 0);  break; //white
			default: color = (255 << 16) | (255 << 8); break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		for (int y = drawStart; y < drawEnd; y++)
			pixput(gui->buffer, x, y, color);
#else
		//texturing calculations
		int texNum = gui->map->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		int	texInd = (texNum * gui->textures.arrsize + side * 2 + ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))) % gui->textures.arrsize;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = gui->cam.posi.y + perpWallDist * rayDirY;
		else          wallX = gui->cam.posi.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(gui->textures.width));
		if(side == 0 && rayDirX > 0) texX = gui->textures.width - texX - 1;
		if(side == 1 && rayDirY < 0) texX = gui->textures.width - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * gui->textures.width / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - gui->cam.pitch - SCRHEIGHT / 2 + lineHeight / 2) * step;
		for(int y = 0; y < SCRHEIGHT; y++)
		{
			if (y < drawStart)
				pixput(gui->buffer, x, y, gui->textures.ceil_col);
			else if (y >= drawEnd)
				pixput(gui->buffer, x, y, gui->textures.floor_col);
			else
			{
				// Cast the texture coordinate to integer, and mask with (gui->textures.width - 1) in case of overflow
				int texY = (int)texPos & (gui->textures.width - 1);
				texPos += step;
				int color = pixget(gui->textures.walls[texInd], gui->textures.width * texY + texX, 0); //gui->textures.textures
				//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				if(side == 1) color = (color >> 1) & 8355711;
				// buffer[y][x] = color;
				pixput(gui->buffer, x, y, color);
			}
		}
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[x] = perpWallDist; //perpendicular distance is used
#endif
	}
}

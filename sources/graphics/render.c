/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/06/16 16:40:01 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

int	pixget(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

void	pixput(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	render(t_gui *gui)
{
	if (gui->rendered && !gui->keys)
		return (0);
	if (gui->keys)
	{
		if (gui->keys & (1 << KP_rot_left))
			rotate(&gui->player, -1);
		else if (gui->keys & (1 << KP_rot_right))
			rotate(&gui->player, 1);
		move(gui);
	}
	t_img	*rend = mlx_new_image(gui->mlx, SCRWIDTH, SCRHEIGHT);

	for(int x = 0; x < SCRWIDTH; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)SCRWIDTH - 1; //x-coordinate in camera space
		double rayDirX = gui->player.dir.x + gui->player.plane.x * cameraX;
		double rayDirY = gui->player.dir.y + gui->player.plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)(gui->player.posi.x);
		int mapY = (int)(gui->player.posi.y);

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
			sideDistX = (gui->player.posi.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - gui->player.posi.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (gui->player.posi.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - gui->player.posi.y) * deltaDistY;
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
			if (mapX >= 24 || mapX < 0 || mapY >= 24 || mapY < 0) // spawn outside map
				return (gui->mlx->end_loop = 1, 42);
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

		int pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCRHEIGHT / 2 + (pitch * SIMPLE);
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCRHEIGHT / 2 + (pitch * SIMPLE);
		if(drawEnd >= SCRHEIGHT) drawEnd = SCRHEIGHT - 1;
#if SIMPLE == 0
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
			pixput(rend, x, y, color);
#else
#define texWidth 64
#define texHeight 64

		int w,h;
		static t_img	*text;
		if (!text) text = mlx_xpm_file_to_image(gui->mlx, "textures/shrek.xpm", &w, &h);

		//texturing calculations
		// int texNum = gui->map->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = gui->player.posi.y + perpWallDist * rayDirY;
		else          wallX = gui->player.posi.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - SCRHEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = pixget(text, texHeight * texY + texX, 0);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			// buffer[y][x] = color;
			pixput(rend, x, y, color);
		}
#endif
	}
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, rend, 0, 0);
	mlx_destroy_image(gui->mlx, rend);
	gui->rendered = 1;
	printf("x%fy%fdirx%fdiry%f\n", gui->player.posi.x, gui->player.posi.y,
									gui->player.dir.x, gui->player.dir.y);
	return (0);
}
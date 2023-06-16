/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/06/15 18:28:10 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

void	pixput(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	render(t_gui *gui)
{
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
			//Check if ray has hit a wall
			if (mapX == 24 || mapX < 0 || mapY == 24 || mapY < 0)
				return (gui->mlx->end_loop = 1, 42);
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

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCRHEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCRHEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCRHEIGHT / 2;
		if(drawEnd >= SCRHEIGHT) drawEnd = SCRHEIGHT - 1;

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
	}
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, rend, 0, 0);
	mlx_destroy_image(gui->mlx, rend);
	printf("x%fy%fdirx%fdiry%f\n", gui->player.posi.x, gui->player.posi.y,
									gui->player.dir.x, gui->player.dir.y);
	return (0);
}
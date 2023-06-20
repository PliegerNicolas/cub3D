/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:41:41 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 17:54:25 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

typedef struct s_ray_caster
{
	int		x;
	int		y;
	int		mapX;
	int		mapY;
	t_vect	rayDir;
	t_vect	sideDist;
	t_vect	deltaDist;
	double	perpWallDist;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}	t_rc;

void	wall_color(t_gui *gui, t_rc *rc)
{
	//choose wall color
	int color;
	switch(gui->map->map[rc->mapX][rc->mapY])
	{
		case 1:  color = (255 << 16);    break; //red
		case 2:  color = (255 << 8);  break; //green
		case 3:  color = (255 << 0);   break; //blue
		case 4:  color = (255 << 16) | (255 << 8) | (255 << 0);  break; //white
		default: color = (255 << 16) | (255 << 8); break; //yellow
	}

	//give x and y sides different brightness
	if (rc->side == 1) {color = color / 2;}

	//draw the pixels of the stripe as a vertical line
	// verLine(x, drawStart, drawEnd, color);
	for (int y = rc->drawStart; y < rc->drawEnd; y++)
		pixput(gui->buffer, rc->x, y, color);
}

// void	wall_texture()
// {
	
// }

void	rays(t_gui *gui, t_rc *rc)
{
	//calculate ray position and direction
	double cameraX = 2 * rc->x / (double)SCRWIDTH - 1; //x-coordinate in camera space
	rc->rayDir.x = (gui->cam.dir.x * gui->cam.zoom) + gui->cam.plane.x * cameraX;
	rc->rayDir.y = (gui->cam.dir.y * gui->cam.zoom) + gui->cam.plane.y * cameraX;
	//which box of the map we're in
	rc->mapX = (int)(gui->cam.posi.x);
	rc->mapY = (int)(gui->cam.posi.y);


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
	rc->deltaDist.x = (rc->rayDir.x == 0) ? 1e30 : fabs(1 / rc->rayDir.x);
	rc->deltaDist.y = (rc->rayDir.y == 0) ? 1e30 : fabs(1 / rc->rayDir.y);

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;
	//calculate step and initial sideDist
	if (rc->rayDir.x < 0)
	{
		stepX = -1;
		rc->sideDist.x = (gui->cam.posi.x - rc->mapX) * rc->deltaDist.x;
	}
	else
	{
		stepX = 1;
		rc->sideDist.x = (rc->mapX + 1.0 - gui->cam.posi.x) * rc->deltaDist.x;
	}
	if (rc->rayDir.y < 0)
	{
		stepY = -1;
		rc->sideDist.y = (gui->cam.posi.y - rc->mapY) * rc->deltaDist.y;
	}
	else
	{
		stepY = 1;
		rc->sideDist.y = (rc->mapY + 1.0 - gui->cam.posi.y) * rc->deltaDist.y;
	}
	//perform DDA
	while(gui->map->map[rc->mapX][rc->mapY] == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->mapX += stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->mapY += stepY;
			rc->side = 1;
		}
	}
	//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
	//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
	//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
	//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
	//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
	//steps, but we subtract deltaDist once because one step more into the wall was taken above.
	if (rc->side == 0)
		rc->perpWallDist = (rc->sideDist.x - rc->deltaDist.x);
	else
		rc->perpWallDist = (rc->sideDist.y - rc->deltaDist.y);

	//Calculate height of line to draw on screen
	rc->lineHeight = (int)(SCRHEIGHT / rc->perpWallDist);

	// int pitch = 100;

	//calculate lowest and highest pixel to fill in current stripe
	rc->drawStart = -rc->lineHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch;
	if (rc->drawStart < 0) rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch;
	if (rc->drawEnd >= SCRHEIGHT) rc->drawEnd = SCRHEIGHT - 1;
}

void	wall_cast(t_gui *gui, double ZBuffer[SCRWIDTH])
{
	t_rc	rc;

	rc.x = 0;
	for(; rc.x < SCRWIDTH; rc.x++)
	{
		rays(gui, &rc);
#define SIMPLE 1
#if SIMPLE == 0
		(void)ZBuffer;
		wall_color(gui, &rc);
#else
		//texturing calculations
		int texNum = gui->map->map[rc.mapX][rc.mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		int	texInd = (texNum * gui->textures.arrsize + rc.side * 2 + ((rc.side == 0 && rc.rayDir.x > 0) || (rc.side == 1 && rc.rayDir.y < 0))) % gui->textures.arrsize;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (rc.side == 0) wallX = gui->cam.posi.y + rc.perpWallDist * rc.rayDir.y;
		else          wallX = gui->cam.posi.x + rc.perpWallDist * rc.rayDir.x;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(gui->textures.width));
		if (rc.side == 0 && rc.rayDir.x > 0) texX = gui->textures.width - texX - 1;
		if (rc.side == 1 && rc.rayDir.y < 0) texX = gui->textures.width - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * gui->textures.width / rc.lineHeight;
		// Starting texture coordinate
		double texPos = (rc.drawStart - gui->cam.pitch - SCRHEIGHT / 2 + rc.lineHeight / 2) * step;
		for(int y = rc.drawStart; y < rc.drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (gui->textures.width - 1) in case of overflow
			int texY = (int)texPos & (gui->textures.width - 1);
			texPos += step;
			int color = pixget(gui->textures.walls[texInd], gui->textures.width * texY + texX, 0); //gui->textures.textures
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (rc.side == 1) color = (color >> 1) & 8355711;
			// buffer[y][x] = color;
			pixput(gui->buffer, rc.x, y, color);
		}
#endif
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[rc.x] = rc.perpWallDist; //perpendicular distance is used
	}
}

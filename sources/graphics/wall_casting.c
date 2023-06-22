/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:41:41 by emis              #+#    #+#             */
/*   Updated: 2023/06/22 16:35:18 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

typedef struct s_ray_caster
{
	int		x;
	int		y;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	t_vect	rayDir;
	t_vect	sideDist;
	t_vect	deltaDist;
	double	perpWallDist;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}	t_rc;

static void	rays(t_gui *gui, t_rc *rc)
{
	if (rc->rayDir.x < 0)
	{
		rc->stepX = -1;
		rc->sideDist.x = (gui->cam.posi.x - rc->mapX) * rc->deltaDist.x;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDist.x = (rc->mapX + 1.0 - gui->cam.posi.x) * rc->deltaDist.x;
	}
	if (rc->rayDir.y < 0)
	{
		rc->stepY = -1;
		rc->sideDist.y = (gui->cam.posi.y - rc->mapY) * rc->deltaDist.y;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDist.y = (rc->mapY + 1.0 - gui->cam.posi.y) * rc->deltaDist.y;
	}
}

static void	cast(t_gui *gui, t_rc *rc)
{
	rays(gui, rc);
	while(gui->map->map[rc->mapX][rc->mapY] == 0)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
	}
	if (rc->side == 0)
		rc->perpWallDist = (rc->sideDist.x - rc->deltaDist.x);
	else
		rc->perpWallDist = (rc->sideDist.y - rc->deltaDist.y);
	rc->lineHeight = (int)(SCRHEIGHT / rc->perpWallDist);
	rc->drawStart = bind(-rc->lineHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch,
		0, SCRHEIGHT);
	rc->drawEnd = bind(rc->lineHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch,
		0, SCRHEIGHT);
}

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

void	wall_texture(t_gui *gui, t_rc *rc)
{
	//texturing calculations
	int texNum = gui->map->map[rc->mapX][rc->mapY] - 1; //1 subtracted from it so that texture 0 can be used!
	int	texInd = (texNum * gui->textures.arrsize + rc->side * 2 + ((rc->side == 0 && rc->rayDir.x > 0) || (rc->side == 1 && rc->rayDir.y < 0))) % gui->textures.arrsize;

	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (rc->side == 0)
		wallX = gui->cam.posi.y + rc->perpWallDist * rc->rayDir.y;
	else
		wallX = gui->cam.posi.x + rc->perpWallDist * rc->rayDir.x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)(wallX * (double)(gui->textures.width));
	if ((rc->side == 0 && rc->rayDir.x > 0)
		|| (rc->side == 1 && rc->rayDir.y < 0))
		texX = gui->textures.width - texX - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * gui->textures.width / rc->lineHeight;
	// Starting texture coordinate
	double texPos = (rc->drawStart - gui->cam.pitch - SCRHEIGHT / 2 + rc->lineHeight / 2) * step;
	for(int y = rc->drawStart; y < rc->drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (gui->textures.width - 1) in case of overflow
		int texY = (int)texPos & (gui->textures.width - 1);
		texPos += step;
		int color = pixget(gui->textures.walls[texInd], gui->textures.width * texY + texX, 0); //gui->textures.textures
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (rc->side == 1) color = (color >> 1) & 8355711;
		// buffer[y][x] = color;
		pixput(gui->buffer, rc->x, y, color);
	}
}

void	wall_cast(t_gui *gui, double ZBuffer[SCRWIDTH])
{
	t_rc	rc;
	double	camX;

	rc.x = 0;
	for(; rc.x < SCRWIDTH; rc.x++)
	{
		camX = 2 * rc.x / (double)SCRWIDTH - 1; //x-coordinate in camera space
		rc.rayDir.x = (gui->cam.dir.x * gui->cam.zoom) + gui->cam.plane.x * camX;
		rc.rayDir.y = (gui->cam.dir.y * gui->cam.zoom) + gui->cam.plane.y * camX;
		rc.mapX = (int)(gui->cam.posi.x);
		rc.mapY = (int)(gui->cam.posi.y);
		rc.deltaDist.x = invSafe(rc.rayDir.x);
		rc.deltaDist.y = invSafe(rc.rayDir.y);
		cast(gui, &rc);
		if (gui->cam.rndr == BASICWALLS)
			wall_color(gui, &rc);
		else
			wall_texture(gui, &rc);
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[rc.x] = rc.perpWallDist; //perpendicular distance is used
	}
}

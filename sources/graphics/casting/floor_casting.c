/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:25:33 by emis              #+#    #+#             */
/*   Updated: 2023/08/09 15:08:27 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

typedef struct rc_floor
{
	float	screen_center;
	float	horizon;
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		texture_x;
	int		texture_y;
}	t_rc_floor;

static void	update_projection_variables(t_gui *gui, t_rc_floor *rc,
	size_t height)
{
	rc->ray_dir_x0 = (gui->cam.dir.x * gui->cam.zoom) - gui->cam.plane.x;
	rc->ray_dir_y0 = (gui->cam.dir.y * gui->cam.zoom) - gui->cam.plane.y;
	rc->ray_dir_x1 = (gui->cam.dir.x * gui->cam.zoom) + gui->cam.plane.x;
	rc->ray_dir_y1 = (gui->cam.dir.y * gui->cam.zoom) + gui->cam.plane.y;
	rc->row_distance = height - rc->horizon;
	if (rc->row_distance != 0)
	{
		if (height > rc->horizon)
			rc->row_distance = rc->screen_center / rc->row_distance;
		else
			rc->row_distance = rc->screen_center / -rc->row_distance;
	}
	rc->floor_step_x = rc->row_distance * (rc->ray_dir_x1 - rc->ray_dir_x0)
		/ SCRWIDTH;
	rc->floor_step_y = rc->row_distance * (rc->ray_dir_y1 - rc->ray_dir_y0)
		/ SCRWIDTH;
}

static void	set_texture_coordinates(t_gui *gui, t_rc_floor *rc)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)rc->floor_x;
	cell_y = (int)rc->floor_y;
	rc->texture_x = (int)(gui->textures.width * (rc->floor_x - cell_x))
		& (gui->textures.width - 1);
	rc->texture_y = (int)(gui->textures.height * (rc->floor_y - cell_y))
		& (gui->textures.height - 1);
}

static void	draw_pixel(t_gui *gui, t_rc_floor *rc, size_t x, size_t y)
{
	int	color;

	if (y > rc->horizon)
	{
		if (gui->textures.floorceil && gui->textures.floorceil[0])
			color = pixget(gui->textures.floorceil[0], gui->textures.width
					* rc->texture_y + rc->texture_x, 0);
		else
			color = gui->textures.floor_color;
	}
	else
	{
		if (gui->textures.floorceil && gui->textures.floorceil[1])
			color = pixget(gui->textures.floorceil[1], gui->textures.width
					* rc->texture_y + rc->texture_x, 0);
		else
			color = gui->textures.ceil_color;
	}
	color = (color >> 1) & 8355711;
	pixput(gui->buffer, x, y, color);
}

void	floor_cast(t_gui *gui)
{
	t_rc_floor	rc;
	size_t		x;
	size_t		y;

	rc.screen_center = 0.5 * SCRHEIGHT;
	rc.horizon = rc.screen_center + (gui->cam.pitch * SCRHEIGHT);
	y = 0;
	while (y < SCRHEIGHT)
	{
		x = 0;
		update_projection_variables(gui, &rc, y);
		rc.floor_x = gui->cam.posi.x + rc.row_distance * rc.ray_dir_x0;
		rc.floor_y = gui->cam.posi.y + rc.row_distance * rc.ray_dir_y0;
		while (x < SCRWIDTH)
		{
			set_texture_coordinates(gui, &rc);
			rc.floor_x += rc.floor_step_x;
			rc.floor_y += rc.floor_step_y;
			draw_pixel(gui, &rc, x, y);
			x++;
		}
		y++;
	}
}

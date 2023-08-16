/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:41:41 by emis              #+#    #+#             */
/*   Updated: 2023/08/16 12:57:17 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	rays(t_play *p, t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_dist.x = (p->posi.x - rc->map_x) * rc->delta_dist.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist.x = (rc->map_x + 1.0 - p->posi.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_dist.y = (p->posi.y - rc->map_y) * rc->delta_dist.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist.y = (rc->map_y + 1.0 - p->posi.y) * rc->delta_dist.y;
	}
}

static void	cast(t_gui *gui, t_rc *rc)
{
	rays(&gui->cam, rc);
	while (gui->map.map[rc->map_x][rc->map_y] % DOOR_OPEN == floor_tile)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
	}
	if (rc->side == floor_tile)
		rc->perp_wall_dist = rc->side_dist.x - rc->delta_dist.x;
	else
		rc->perp_wall_dist = rc->side_dist.y - rc->delta_dist.y;
	rc->line_height = (int)(SCRHEIGHT / rc->perp_wall_dist);
	rc->draw_start = bind(-rc->line_height / 2 + SCRHEIGHT
			/ 2 + (gui->cam.pitch * SCRHEIGHT), 0, SCRHEIGHT);
	rc->draw_end = bind(rc->line_height / 2 + SCRHEIGHT
			/ 2 + (gui->cam.pitch * SCRHEIGHT), 0, SCRHEIGHT);
}

void	wall_cast(t_gui *gui, double z_buffer[SCRWIDTH])
{
	t_play	*p;
	t_rc	rc;
	double	cam_x;

	p = &gui->cam;
	rc.x = 0;
	while (rc.x < SCRWIDTH)
	{
		cam_x = 2 * rc.x / (double)SCRWIDTH - 1;
		rc.ray_dir.x = p->dir.x * p->zoom + p->plane.x * cam_x;
		rc.ray_dir.y = p->dir.y * p->zoom + p->plane.y * cam_x;
		rc.map_x = (int)p->posi.x;
		rc.map_y = (int)p->posi.y;
		rc.delta_dist.x = inv_safe(rc.ray_dir.x);
		rc.delta_dist.y = inv_safe(rc.ray_dir.y);
		cast(gui, &rc);
		if (is_mask_set(&gui->cam, TEXTUWALLS))
			wall_texture(gui, &rc);
		else
			wall_color(gui, &rc);
		z_buffer[rc.x++] = rc.perp_wall_dist;
	}
}

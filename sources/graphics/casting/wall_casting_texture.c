/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:15:05 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/15 15:20:56 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

typedef struct s_texture_data
{
	int		id;
	int		x;
	int		y;
	double	step;
	double	pos;
}	t_texture_data;

static int	get_texture_id(t_gui *gui, t_rc *rc)
{
	int	tex_num;
	int	tex_id;

	tex_num = gui->map.map[rc->map_x][rc->map_y] - 1;
	tex_id = tex_num * gui->textures.arrsize;
	tex_id += rc->side * 2;
	if (rc->side == 0 && rc->ray_dir.x > 0)
		tex_id += 1;
	else if (rc->side == 1 && rc->ray_dir.y < 0)
		tex_id += 1;
	return (tex_id % gui->textures.arrsize);
}

static int	get_texture_x(t_gui *gui, t_rc *rc)
{
	double	wall_x;
	int		texture_x;

	if (rc->side == 0)
		wall_x = gui->cam.posi.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wall_x = gui->cam.posi.x + rc->perp_wall_dist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)gui->textures.width);
	if ((rc->side == 0 && rc->ray_dir.x > 0)
		|| (rc->side == 1 && rc->ray_dir.y < 0))
		texture_x = gui->textures.width - texture_x - 1;
	return (texture_x);
}

static t_texture_data	initialize_tex_data(t_gui *gui, t_rc *rc)
{
	t_texture_data	tex_data;

	tex_data.id = get_texture_id(gui, rc);
	tex_data.x = get_texture_x(gui, rc);
	tex_data.step = 1.0 * gui->textures.width / rc->line_height;
	tex_data.pos = (rc->draw_start - (gui->cam.pitch * SCRHEIGHT) - SCRHEIGHT
			/ 2 + rc->line_height / 2) * tex_data.step;
	return (tex_data);
}

void	wall_texture(t_gui *gui, t_rc *rc)
{
	t_texture_data	tex_data;
	int				y;
	int				color;

	tex_data = initialize_tex_data(gui, rc);
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		tex_data.y = (int)tex_data.pos & (gui->textures.width - 1);
		tex_data.pos += tex_data.step;
		if (gui->map.map[rc->map_x][rc->map_y] == DOOR_CLOSED
			&& gui->textures.doors)
			color = pixget(gui->textures.doors[0],
					gui->textures.width * tex_data.y + tex_data.x, 0);
		else
			color = pixget(gui->textures.walls[tex_data.id],
					gui->textures.width * tex_data.y + tex_data.x, 0);
		if (gui->cam.dark)
			color = color_mixer(color, 0, bind(gui->cam.dark
						* (rc->perp_wall_dist + 1), 0, 255));
		pixput(gui->buffer, rc->x, y++, color);
	}
}

void	wall_color(t_gui *gui, t_rc *rc)
{
	int	color;
	int	y;

	if (gui->map.map[rc->map_x][rc->map_y] == 1)
		color = (255 << 16);
	else if (gui->map.map[rc->map_x][rc->map_y] == 2)
		color = (255 << 8);
	else if (gui->map.map[rc->map_x][rc->map_y] == 3)
		color = (255 << 0);
	else if (gui->map.map[rc->map_x][rc->map_y] == 4)
		color = (255 << 16) | (255 << 8) | (255 << 0);
	else
		color = (255 << 16) | (255 << 8);
	if (rc->side == 1)
		color /= 2;
	y = rc->draw_start;
	while (y < rc->draw_end)
		pixput(gui->buffer, rc->x, y++, color);
}

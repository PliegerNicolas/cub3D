/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/08/12 13:21:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	raycast_projectile(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;
	double	distance;
	bool	target_hit;

	target_hit = !move_projectile(gui, projectile);

	distance = calc_distance(gui->cam.posi, projectile->posi);

	rc.ray_dir.x = (projectile->posi.x - gui->cam.posi.x) * gui->cam.zoom;
	rc.ray_dir.y = (projectile->posi.y - gui->cam.posi.y) * gui->cam.zoom;

	double	inv_det = 1.0 / (gui->cam.plane.x * rc.ray_dir.y - rc.ray_dir.x * gui->cam.plane.y);
	double	transf_x = inv_det * (gui->cam.dir.y * rc.ray_dir.x - gui->cam.dir.x * rc.ray_dir.y);

	int	screen_x = (SCRWIDTH / 2.0) * (1.0 + transf_x);
	int	screen_y = (SCRHEIGHT / 2.0) + (gui->cam.pitch * SCRHEIGHT);

	if (!target_hit && is_projectile_obstructed(gui, projectile))
		return (false);
	else
	{
		if (target_hit)
			return (draw_projectile_impact(gui, screen_x, screen_y, distance), true);
		else
			draw_projectile(gui, screen_x, screen_y, distance);
	}
	return (false);
}

static void	attack(t_gui *gui, t_prj *projectile)
{
	if (raycast_projectile(gui, projectile))
		clear_projectile(projectile);
}

void	weapon(t_gui *gui)
{
	static t_prj	projectile;
	static int		walk_frame;
	int				weapon_x;
	int				weapon_y;

	if (!gui->textures.weapon)
		return ;
	weapon_x = 0;
	weapon_y = 0;
	walk_frame = calculate_next_walk_frame(gui, walk_frame);
	set_weapon_position(gui, &weapon_x, &weapon_y, walk_frame);
	if (!projectile.status && (gui->btns & (1 << left_click)))
		initialize_projectile(&gui->cam, &projectile);
	if (projectile.status)
		attack(gui, &projectile);
	imgput(gui->buffer, weapon_x, weapon_y, gui->textures.weapon);
}
